from XInput import get_connected, get_thumb_values, get_state,get_button_values;
import serial
import time
import struct


def dir_map(joystickLeft):
    x = joystickLeft[0]
    y = joystickLeft[1]
    print(x,y)
    if (x > -0.4) and (x < 0.4) and (y > -0.4) and (y < 0.4):
        return 0
    if (y > -x) and (y < x):
        return 3
    if (y > x) and (y < -x): 
        return 2
    if (y >= abs(x)):
        return 1
    if (y < abs(x)):
        return 4
    return 0

def c_map(In, in_min, in_max, out_min, out_max):
    return ( (In - in_min) * (out_max - out_min) ) / ( (in_max - in_min) + out_min )

def vel_map(joystickLeft, dir):
    x = joystickLeft[0]
    y = joystickLeft[1]
    
    if (dir==1):
        return c_map(y,0.4, 1, 0, 255)
    if (dir==4):
        return c_map(-y, 0.4, 1, 0, 255)
    if (dir==2):
        return c_map(-x, 0.4, 1, 0, 255)
    if (dir==3):
        return c_map(x,0.4, 1, 0, 255)
    
    return 0


if __name__ == '__main__':
    port = 'COM4'    
    try:
        ser = serial.Serial(port, 9600)
        datos = [0,0]
        if get_connected()[0] == True:
            print('Hay un control conectado')
            while True:
                (joystickLeft, joystickRight) = get_thumb_values(get_state(0));
                if get_button_values(get_state(0))["A"] == True:
                    ser.close()
                    break;
                
                datos[1] = dir_map(joystickLeft)
                datos[0] = vel_map(joystickLeft, datos[1]);
                
                print(datos[0], datos[1])
                
                #print(bytearray([int(datos[0]), int(datos[1])]))
                #print(struct.pack("BB", int(datos[0]),  int(datos[1])))
                
                ser.write(struct.pack("BB", int(datos[0]),  int(datos[1])))
                print(struct.pack("BB", int(datos[0]),  int(datos[1])))
                time.sleep(0.05)
        else:
            print('No hay un control conectado')
    except TimeoutError:
        print('Error al conectar el arduino')
    finally:
        print('Listo')
