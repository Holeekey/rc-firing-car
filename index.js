const { SerialPort } = require('serialport')
const readline = require('readline');

const port = new SerialPort({
    path:'COM4',
    baudRate: 9600,
})

readline.emitKeypressEvents(process.stdin);
if (process.stdin.isTTY) process.stdin.setRawMode(true);

process.stdin.on('keypress', (chunk, key) => {
    if(!key) return;
    switch(key.name){
        case 'up':
            return port.write([255,1]); //arriba
        case 'down':
            return port.write([1,255]); //abajo
        case 'left':
            return port.write([255,255]); //izquierda
        case 'right':
            return port.write([1,1]); //derecha
        case 'w' :
            return port.write([255,1]); //arriba
        case 's' :
            return port.write([1,255]); //abajo
        case 'a' :
            return port.write([255,255]); //izquierda
        case 'd' :
            return port.write([1,1]); //derecha
        case 'q':
            return process.quit();
    }
});
