const htmlGame = document.querySelector("#container");

const Direction = {
    Up : 'Up',
    Down : 'Down',
    Rigth : 'Rigth',
    Left : 'Left'
};

UP = Direction.Up;
DOWN = Direction.Down;
RIGTH = Direction.Rigth;
LEFT = Direction.Left;

class Game {
    
    constructor(board, witness, size) {

        this.board = board;
        this.witness = witness;

        if (size * size !== this.board.length || this.board.length !== this.witness.length) { 
            if (size * size !== this.board.length) console.error("Miss match \'size\'", size * size ,"with \'size board\' ", this.board.length);
            if (this.board.length !== this.witness.length) console.error("Miss match \'board size\'", this.board.length, "with \'witness size\'", this.witness.length);
            this.board = undefined;
            this.size = undefined;
            this.witness = undefined;
        }
        else { 
            this.size = size;
            this.totalSize = size * size;
        }
    }

    get getSize() { return this.size; }

    setIndiceBoard(i, value) { this.board[i] = value; }

    nextMove(dir, indice) {
        switch (dir) {
            case UP: this.shiftU(indice);break;
            case DOWN : this.shiftD(indice);break;
            case RIGTH : this.shiftR(indice);break;
            case LEFT : this.shiftL(indice);break;
            default : console.error("Unknow direction", dir); 
        }
    }

    display() {
        for (let i = 0; i <= this.totalSize - this.size; i += this.size) 
            console.log(...(this.board.slice(i, i + this.size))); 
    }

    shiftU(indice){
        let indicecourant = this.size + indice;
        let tmp = this.board[indice];
        for (let i = 0; i < this.size - 1; i++) {
            this.setIndiceBoard(indice + (i*this.size),this.board[indicecourant]);
            indicecourant += this.size;
        }
        indicecourant -= this.size;
        this.setIndiceBoard(indicecourant, tmp);
    }

    shiftD(indice){
        for (let i = 0; i < this.size - 1; i++) this.shiftU(indice); 
    }

    shiftL(indice) {        
        let temp = this.board[indice * this.size];
        for (let i = indice * this.size + 1; i < (indice + 1) * this.size; i++)
            this.setIndiceBoard(i - 1,this.board[i]);
        this.setIndiceBoard((indice + 1) * this.size - 1, temp);
    }
    
    shiftR(indice) {
        let temp = this.board[(indice + 1) * this.size - 1];
        for (let i = (indice + 1) * this.size - 1; i > indice * this.size - 1; i--) {
            this.setIndiceBoard(i,this.board[i-1]);
        }
        this.setIndiceBoard(indice * this.size, temp);
    }

    shuffle() {
        for (let i = 0; i < 100; i++)
        {
            let alea =  Math.floor(Math.random() * 4);
            let indicealea = Math.floor(Math.random() * this.size);
            switch (alea) {
                case 0: this.shiftL(indicealea);break;
                case 1: this.shiftR(indicealea);break;
                case 2: this.shiftU(indicealea);break;
                case 3: this.shiftD(indicealea);break;
            }
        }
    }

    render() {
        // <div class="child-box"></div>
        const boxes = document.querySelector(".box");
        boxes.style.width = (this.size * 6 + 2).toString() + "em";

        while (htmlGame.hasChildNodes()) {  
            htmlGame.removeChild(htmlGame.firstChild);
        }

        this.board.forEach(elem => {
            const temp = document.createElement("div");
            temp.className += " child-box";
            temp.innerHTML = elem;
            htmlGame.appendChild(temp);
        });
    }
}

let a = new Game([1,2,3,4,5,6,7,8,9,4,11,12,13,14,15,16],[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16] , 4);
a.shuffle();
a.render();
