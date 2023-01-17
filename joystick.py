from XInput import get_connected, get_thumb_values, get_state,get_button_values, EVENT_BUTTON_PRESSED, get_events, Event;
import serial
import time
import struct


def dir_map(joystickLeft):
    x = joystickLeft[0]
    y = joystickLeft[1]
    #print(x,y)
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


def canon_dir_map(grados, joystickRight):
    x = joystickRight[0];

    if(x > -0.4) and (x < 0.4):
        return grados;

    res = grados + c_map(x, 0.4, 1, 0, 3) 

    if res > 180: 
        return 180
    elif res < 0:
        return 0
    else:
        return res 

if __name__ == '__main__':
    port = 'COM4'    
    try:
        ser = serial.Serial(port, 9600)
        datos = [0,0,0,90]
        if get_connected()[0] == True:

            print('Hay un control conectado')
            user_index = 0

            while True:    
                state = get_state(user_index);

                (joystickLeft, joystickRight) = get_thumb_values(state);

                a_button = get_button_values(state)["A"]
                b_button = get_button_values(state)["B"]

                if b_button == True :
                    ser.close()
                    break;

                datos[1] = dir_map(joystickLeft)
                datos[0] = vel_map(joystickLeft, datos[1])
                datos[2] = a_button
                datos[3] = canon_dir_map(datos[3], joystickRight)

                byte_message = struct.pack("BBBB", int(datos[0]),  int(datos[1]), int(datos[2]), int(datos[3]))

                print(datos[0], datos[1], datos[2], datos[3])                
                print(byte_message)

                ser.write(byte_message)
                
                time.sleep(0.05)
        else:
            print('No hay un control conectado')
    except TimeoutError:
        print('Error al conectar el arduino')
    finally:
        print('Listo')
