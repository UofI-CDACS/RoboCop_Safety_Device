#  pip install modbus
from pymodbus.client.tcp import ModbusTcpClient

# Configuration
SERVER_IP = "129.101.98.242"  # Modbus server IP, displayed in RoboCop
SERVER_PORT = 502             # Modbus server port
REGISTER_ADDRESS = 5          # Address of the holding register to read from

def main():
    """Function to read distance data from Modbus holding register."""
    # Create Modbus client
    client = ModbusTcpClient(SERVER_IP, port=SERVER_PORT)

    # Attempt to connect to the Modbus server
    if client.connect():
        print("Successfully connected to the Modbus server.")

        try:
            # Read the specified holding register
            response = client.read_holding_registers(REGISTER_ADDRESS, count=1)

            # Check if the response is valid
            if response and not response.isError():
                # Extract and process the distance data
                raw_distance = response.registers[0]  # Value goten from register
                distance_cm = raw_distance / 100.0   # Convert to centimeters, change to suit your use-case
                print(f"Distance measured: {distance_cm:.2f} cm")
            else:
                print(f"Error reading register: {response}")

        except Exception as e:
            # Exception handling during Modbus operations
            print(f"An error occurred: {e}")

        finally:
            # Ensure the client is properly closed
            client.close()
            print("Connection to Modbus server closed.")
    else:
        print("Unable to connect to the Modbus server. Please check the network settings.")

# Run script
if __name__ == "__main__":
    main()
