import socket
import sys

# Creando un socket TCP/IP
# An INET, STREAMing socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Conecta el socket en el puerto cuando el servidor esté escuchando
server_address = ('192.168.0.6', 22)
print('Conectando a %s puerto %s ...\n' % server_address)
sock.connect(server_address)

try:
    # Enviando datos
    message = "Hola servidor. Soy cliente."
    print('Enviando... "%s"' % message)
    sock.sendall(message.encode("utf-8"))

    # Buscando respuesta
    amount_received = 0
    amount_expected = 51
    
    while amount_received < amount_expected:
        data = sock.recv(amount_expected)
        amount_received += len(data)
        print('Recibido: "%s"' % data.decode("utf-8"))

finally:
    print("\nCerrando socket... \nFinalizó conexión.")
    sock.close()


# https://pythondiario.com/2015/01/simple-programa-clienteservidor-socket.html
