const htmlGame = document.querySelector("#game");
const htmlWitness = document.querySelector("#witness");
const shuffle = document.getElementById("shuffle");
const buttons_up = document.getElementById("buttons_up");
const buttons_down = document.getElementById("buttons_down")
const buttons_left = document.getElementById("buttons_left")
const buttons_right = document.getElementById("buttons_right")

const maxSize = 2;
const finalSize = Math.floor(Math.random() * maxSize) + 5

const colors = [
    "#00FFFF",
    "#00FF00",
    "#FF0000",
    "#FF00FF",
    "#00BFFF",
    "#A0522D",
    "#F0FFFF",
    "#ADFF2F",
    "#A52A2A",
    "#8B008B",
    "#DDA0DD",
    "#696969",
    "#FFFFF0"
]


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
        
        htmlGame.style.width = (this.size * 4 + 2).toString() + "em";
        htmlWitness.style.width = (this.size * 3 + 2).toString() + "em";
        while (htmlGame.hasChildNodes()) htmlGame.removeChild(htmlGame.firstChild);

        this.board.forEach(elem => {
            const temp = document.createElement("div");
            temp.className += "child-box-game";
            temp.style.backgroundColor = elem;
            htmlGame.appendChild(temp);
        });

        while (htmlWitness.hasChildNodes()) htmlWitness.removeChild(htmlWitness.firstChild);

        this.witness.forEach(elem => {
            const temp = document.createElement("div");
            temp.className += "child-box-witness";
            temp.style.backgroundColor = elem;
            htmlWitness.appendChild(temp);
        });

        for (let i = 0; i < this.totalSize; i++) {
            if (this.board[i] !== this.witness[i]) return 
        }
        console.log("gagne")
        
    }
}

let res = []
for (let index = 0; index < finalSize*finalSize; index++) {
    let color = colors[Math.floor(Math.random() * 12)]
    res.push(color)
}

let res_ = res.slice();

let a = new Game(res, res_, finalSize)

for(let i = 0; i < a.size * 4; i++){
    const temp = document.createElement("button");
    const mfia = Math.floor(i / a.size);

    switch(mfia) {
        case 0:
            temp.innerHTML = `<i class="fas fa-chevron-up"></i>`;
            temp.onclick = (() => {a.nextMove(UP, i % a.size);a.render();});
            temp.id = `${UP}${i % a.size + 1}`;
            buttons_up.appendChild(temp);
            break;
        case 1:
            temp.innerHTML = `<i class="fas fa-chevron-down"></i>`;
            temp.onclick = (() => { a.nextMove(DOWN, i % a.size); a.render(); });
            temp.id = `${DOWN}${i % a.size + 1}`;
            buttons_down.appendChild(temp);
            break;
        case 2:
            temp.innerHTML = `<i class="fas fa-chevron-left"></i>`;
            temp.onclick = (() => { a.nextMove(LEFT, i % a.size); a.render(); });
            temp.id = `${LEFT}${i % a.size + 1}`;
            buttons_left.appendChild(temp);
            break;
        case 3:
            temp.innerHTML = `<i class="fas fa-chevron-right"></i>`;
            temp.onclick = (() => { a.nextMove(RIGHT, i % a.size); a.render(); });
            temp.id = `${RIGHT}${i % a.size + 1}`;
            buttons_right.appendChild(temp);
            break;
    }

    //buttons.appendChild(temp);
}




const temp = document.createElement("button");
temp.innerHTML = "SHUFFLE";
temp.onclick = (() => {a.shuffle(); a.render();});
shuffle.appendChild(temp);

a.render();