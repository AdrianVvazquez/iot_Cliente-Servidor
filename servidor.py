import socket

# Enlace de socket y puerto
SERVER_ADDRESS = ('192.168.0.6', 22)
msn_1 = 'Hola cliente, te conectaste a servidor, bienvenido.'

# Creando el socket TCP/IP
serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print('Empezando a levantar %s puerto %s' % SERVER_ADDRESS)
serversocket.bind(SERVER_ADDRESS)   # Asociar socket a direccion

# Escuchando conexiones entrantes
serversocket.listen(1)

while True:
    # Esperando conexion
    print('Conectando...')
    (connection, client_address) = serversocket.accept()

    try:
        print('Conexión desde', client_address, "\n")
        # Recibe los datos en trozos y reetransmite
        while True:
            data = connection.recv(len(msn_1))
            if data:
                print('Recibido: "%s"' % data.decode("utf-8"))
                print('Enviando... mensaje al cliente...')
                connection.sendall(msn_1.encode("utf-8"))
            else:
                print('\nNo hay mas datos. Finalizando transmisión con...', client_address)
                break
            
    finally:
        # Cerrando conexion
        connection.close()
