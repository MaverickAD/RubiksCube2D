const htmlGame = document.querySelector("#game");
  
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
        while (htmlGame.hasChildNodes()) htmlGame.removeChild(htmlGame.firstChild);

        this.board.forEach(elem => {
            const temp = document.createElement("div");
            temp.style.width = "4em";
            temp.style.height = "4em";
            temp.className += "droppable child-box-game";
            temp.style.backgroundColor = elem;
            htmlGame.appendChild(temp);
        });
    }
}   

let a = new Game(["#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff"
                 ,"#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff"
                 ,"#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff"
                 ,"#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff"
                 ,"#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff"
                 ,"#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff"
                 ,"#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff"]
                 ,
                 ["#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff"
                 ,"#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff"
                 ,"#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff"
                 ,"#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff"
                 ,"#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff"
                 ,"#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff"
                 ,"#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff"], 7);

a.render();




const draggableElements = document.querySelectorAll(".draggable");
const droppableElements = document.querySelectorAll(".droppable");

console.log(draggableElements)

draggableElements.forEach(elem => {
    elem.addEventListener("dragstart", dragStart);
});

droppableElements.forEach(elem => {
    elem.addEventListener("dragover", dragOver); // Fires when a dragged item is being dragged over a valid drop target, repeatedly while the draggable item is within the drop zone
    elem.addEventListener("drop", drop); // Fires when an item is dropped on a valid drop target
});

function dragStart(event) {
    console.log("prount")
    console.log(event.target.style.color)
    event.dataTransfer.setData("text", event.target.style.backgroundColor);
}

function dragOver(event){
    event.preventDefault()
}

function drop(event) {
    event.preventDefault();
    const data = event.dataTransfer.getData("text")
    event.target.style.backgroundColor = data;
}