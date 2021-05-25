const htmlGame = document.querySelector("#container")
const buttons = document.querySelector("#buttons")

const Direction = {
    Up: 'Up',
    Down: 'Down',
    Right: 'Right',
    Left: 'Left'
}

UP = Direction.Up;
DOWN = Direction.Down;
RIGHT = Direction.Right;
LEFT = Direction.Left;

class Game {
    
    constructor (board, witness, size)
    {

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

    display() {
        for (let i = 0; i <= this.totalSize - this.size; i += this.size) 
            console.log(...(this.board.slice(i, i + this.size))); 
    }

    nextMove(dir, indice) {
        switch (dir) {
            case 'Up': this.shiftU(indice);break;
            case 'Down' : this.shiftD(indice);break;
            case 'Right' : this.shiftR(indice);break;
            case 'Left' : this.shiftL(indice);break;
            default : console.error("Unknow direction", dir);break; 
        }
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
        const boxes = document.querySelector(".box");
        boxes.style.width = (this.size * 6 + 2).toString() + "em";

        while (htmlGame.hasChildNodes()) htmlGame.removeChild(htmlGame.firstChild);

        this.board.forEach(elem => {
            const temp = document.createElement("div");
            temp.className += " child-box";
            temp.style.backgroundColor = elem;
            htmlGame.appendChild(temp);
        });
    }
}

let a = new Game(["#aba5a7","#aba5a7","#c2eef0","#aba5a7","#aba5a7"
                 ,"#c2eef0","#b99a5e","#b99a5e","#b99a5e","#c2eef0"
                 ,"#b99a5e","#aba5a7","#ffffff","#aba5a7","#b99a5e"
                 ,"#f37a7a","#ffffff","#aba5a7","#ffffff","#f37a7a"
                 ,"#ffffff","#aba5a7","#e1b1dd","#aba5a7","#ffffff"]
                 , [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1], 5);

for(let i = 0; i < a.size * 4; i++){
    const temp = document.createElement("button");
    const mfia = Math.floor(i / a.size);

    switch(mfia) {
        case 0:
            temp.innerHTML = `${UP} ${i % a.size + 1}`;
            temp.onclick = (() => {a.nextMove(UP, i % a.size);a.render();});
            break;
        case 1:
            temp.innerHTML = `${DOWN} ${i % a.size + 1}`;
            temp.onclick = (() => { a.nextMove(DOWN, i % a.size); a.render(); });
            break;
        case 2:
            temp.innerHTML = `${LEFT} ${i % a.size + 1}`;
            temp.onclick = (() => { a.nextMove(LEFT, i % a.size); a.render(); });
            break;
        case 3:
            temp.innerHTML = `${RIGHT} ${i % a.size + 1}`;
            temp.onclick = (() => { a.nextMove(RIGHT, i % a.size); a.render(); });
            break;
    }

    buttons.appendChild(temp);
}

const temp = document.createElement("button");
temp.innerHTML = "SHUFFLE";
temp.onclick = (() => {a.shuffle(); a.render();});
buttons.appendChild(temp);

a.render();
