import socket

def solution(host, port):
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((host, port))
            print(f"Connected to {host}:{port}")
            
            buffer = b""
            
            def send_command(command):
                s.sendall(f"{command}\n".encode())
                buffer = b""
                while b'>>' not in buffer:
                    data = s.recv(1024)
                    if not data:
                        raise ConnectionError("Connection closed by server.")
                    buffer += data
                if command == 2:
                    print(buffer.decode(), end="")

            for _ in range(16):
                send_command(3)
            
            send_command(2)

            flag_data = s.recv(1024)
            print("\nFlag received:")
            print(flag_data.decode().strip())
            
    except Exception as e:
        print(f"An error occurred: {e}")

HOST = "127.0.0.1"
PORT = 1337

if __name__ == "__main__":
    solution(HOST, PORT)
