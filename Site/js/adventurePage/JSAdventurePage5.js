const htmlGame = document.querySelector("#game");
const htmlWitness = document.querySelector("#witness");
const shuffle = document.getElementById("shuffle");
const buttonsTop = document.getElementById("buttonsTop");
const buttonsBottom = document.getElementById("buttonsBottom")
const buttonsLeft = document.getElementById("buttonsLeft")
const buttonsRight = document.getElementById("buttonsRight")
const cornerTopLeft = document.getElementById("cornerTopLeft");
const cornerTopRight = document.getElementById("cornerTopRight");
const cornerBottomLeft = document.getElementById("cornerBottomLeft");
const cornerBottomRight = document.getElementById("cornerBottomRight");
const popup = document.querySelector("div#popup");

const sizeIntoHtml = 5;

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
        this.isWin = false;
        this.isStart = false;

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
        
        htmlGame.style.width = (this.size * sizeIntoHtml).toString() + "em";
        htmlGame.style.height = (this.size * sizeIntoHtml).toString() + "em";
        htmlGame.style.margin = (this.size * 0.1).toString() + "em"
        htmlWitness.style.width = (this.size * 3).toString() + "em";
        while (htmlGame.hasChildNodes()) htmlGame.removeChild(htmlGame.firstChild);

        this.board.forEach(elem => {
            const temp = document.createElement("div");
            temp.className += "child-box-game";
            temp.style.backgroundColor = elem;
            temp.style.width = sizeIntoHtml + "em";
            temp.style.height = sizeIntoHtml + "em";
            temp.style.border = "solid black"
            htmlGame.appendChild(temp);
        });

        while (htmlWitness.hasChildNodes()) htmlWitness.removeChild(htmlWitness.firstChild);

        this.witness.forEach(elem => {
            const temp = document.createElement("div");
            temp.className += "child-box-witness";
            temp.style.backgroundColor = elem;
            temp.style.width = sizeIntoHtml - 2 + "em";
            temp.style.height = sizeIntoHtml - 2 + "em";
            temp.style.border = "solid black"
            htmlWitness.appendChild(temp);
        });

        for (let i = 0; i < this.totalSize; i++) {
            if (this.board[i] !== this.witness[i]) return 
        }
        this.isWin = true;
        if (this.isStart) {
            chronoStop();
            const filter = document.querySelector("div.filter");
            filter.classList.toggle = "expanded"
            popup.style.opacity = "1"
            popup.style.display = "flex"
        }
    }
}

let a = new Game(["#000000","#FF6060","#ff0000","#ff0000","#ff0000","#FF6060","#000000"
,"#00C3FF","#000000","#FF6060","#ff0000","#FF6060","#000000","#FFFF9F"
,"#0000ff","#00C3FF","#454545","#454545","#454545","#FFFF9F","#ffff00"
,"#0000ff","#0000ff","#454545","#454545","#454545","#ffff00","#ffff00"
,"#0000ff","#00C3FF","#454545","#454545","#454545","#FFFF9F","#ffff00"
,"#00C3FF","#000000","#80FF80","#00ff00","#80FF80","#000000","#FFFF9F"
,"#000000","#80FF80","#00ff00","#00ff00","#00ff00","#80FF80","#000000"]

,["#000000","#FF6060","#ff0000","#ff0000","#ff0000","#FF6060","#000000"
,"#00C3FF","#000000","#FF6060","#ff0000","#FF6060","#000000","#FFFF9F"
,"#0000ff","#00C3FF","#454545","#454545","#454545","#FFFF9F","#ffff00"
,"#0000ff","#0000ff","#454545","#454545","#454545","#ffff00","#ffff00"
,"#0000ff","#00C3FF","#454545","#454545","#454545","#FFFF9F","#ffff00"
,"#00C3FF","#000000","#80FF80","#00ff00","#80FF80","#000000","#FFFF9F"
,"#000000","#80FF80","#00ff00","#00ff00","#00ff00","#80FF80","#000000"], 7);

for(let i = 0; i < a.size * 4; i++){
    const temp = document.createElement("div");
    const mfia = Math.floor(i / a.size);

    temp.classList.add("buttonWithAction");
    temp.style.width = sizeIntoHtml + "em";
    temp.style.height = sizeIntoHtml + "em";

    switch(mfia) {
        case 0:
            temp.innerHTML = `<i class="fas fa-chevron-up"></i>`;
            temp.onclick = (() => {a.nextMove(UP, i % a.size);a.render();});
            temp.id = `${UP}${i % a.size + 1}`;
            buttonsTop.appendChild(temp);
            break;
        case 1:
            temp.innerHTML = `<i class="fas fa-chevron-down"></i>`;
            temp.onclick = (() => { a.nextMove(DOWN, i % a.size); a.render(); });
            temp.id = `${DOWN}${i % a.size + 1}`;
            buttonsBottom.appendChild(temp);
            break;
        case 2:
            temp.innerHTML = `<i class="fas fa-chevron-left"></i>`;
            temp.onclick = (() => { a.nextMove(LEFT, i % a.size); a.render(); });
            temp.id = `${LEFT}${i % a.size + 1}`;
            buttonsLeft.appendChild(temp);
            break;
        case 3:
            temp.innerHTML = `<i class="fas fa-chevron-right"></i>`;
            temp.onclick = (() => { a.nextMove(RIGHT, i % a.size); a.render(); });
            temp.id = `${RIGHT}${i % a.size + 1}`;
            buttonsRight.appendChild(temp);
            break;
    }

    //buttons.appendChild(temp);
}

cornerTopLeft.style.width = sizeIntoHtml + "em";
cornerTopLeft.style.height = sizeIntoHtml + "em";
cornerTopLeft.style.margin = "0.1em"

buttonsTop.style.width = a.size * (sizeIntoHtml + 0.2) + "em";
buttonsTop.style.height = (sizeIntoHtml + 0.2) + "em";

cornerTopRight.style.width = sizeIntoHtml + "em";
cornerTopRight.style.height = sizeIntoHtml + "em";
cornerTopRight.style.margin = "0.1em"

buttonsLeft.style.width = (sizeIntoHtml + 0.2) + "em";
buttonsLeft.style.height =  a.size * (sizeIntoHtml + 0.2) + "em";

buttonsRight.style.width = (sizeIntoHtml + 0.2) + "em";
buttonsRight.style.height = a.size * (sizeIntoHtml + 0.2) + "em";

cornerBottomLeft.style.width = sizeIntoHtml + "em";
cornerBottomLeft.style.height = sizeIntoHtml + "em";
cornerBottomLeft.style.margin = "0.1em"

buttonsBottom.style.width = a.size * (sizeIntoHtml + 0.2) + "em";
buttonsBottom.style.height = (sizeIntoHtml + 0.2) + "em";

cornerBottomRight.style.width = sizeIntoHtml + "em";
cornerBottomRight.style.height = sizeIntoHtml + "em";
cornerBottomRight.style.margin = "0.1em"

const temp = document.createElement("div");
temp.id = "buttonShuffle";
temp.innerHTML = "SHUFFLE";
temp.onclick = (() => {
    if (!a.isStart){ a.isStart = !a.isStart }
    a.shuffle(); a.render();
    chronoStart();
    });

shuffle.appendChild(temp);

a.render();
