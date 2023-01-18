const { SerialPort } = require('serialport')
const readline = require('readline');

const port = new SerialPort({
    path:'COM4',
    baudRate: 9600,
})

readline.emitKeypressEvents(process.stdin);
if (process.stdin.isTTY) process.stdin.setRawMode(true);

posCanon = 90
dir = 0
vel = 0
isMovingCanon = false
isShooting = false

process.stdin.on('keypress', (chunk, key) => {
    if(!key) return;
    isMoving = true;
    switch(key.name){
        case 'w' :
            dir = 1
            vel = key.ctrl ? 255 : 180
            return port.write([vel,dir,isShooting ? 1 : 0,posCanon]); //arriba
        case 's' :
            dir = 4
            vel = key.ctrl ? 255 : 180
            return port.write([vel,dir,isShooting ? 1 : 0,posCanon]); //abajo
        case 'a' :
            dir = 2
            vel = key.ctrl ? 255 : 180
            return port.write([vel,dir,isShooting ? 1 : 0,posCanon]); //izquierda
        case 'd' :
            dir = 3
            vel = key.ctrl ? 255 : 180
            return port.write([vel,dir,isShooting ? 1 : 0,posCanon]); //derecha
        case 'space':
            dir = 0
            vel = 0
            return port.write([vel,dir,isShooting ? 1 : 0,posCanon]); //stop
        case 'left':
            isMovingCanon = !isMovingCanon
            return port.write([vel,dir,isShooting ? 1 : 0,isMovingCanon && posCanon-3 > 0 ? posCanon-3 : posCanon]); //izquierda cañon
        case 'right':
            isMovingCanon = !isMovingCanon
            return port.write([vel,dir,isShooting ? 1 : 0,isMovingCanon && posCanon+3 < 180 ? posCanon+3 : posCanon]); //derecha cañon
        case 'p' :
            isShooting = !isShooting;
            return port.write([vel,dir,isShooting ? 1 : 0,posCanon]); //disparo
        case 'q':
            return process.exit();
    } 
});
