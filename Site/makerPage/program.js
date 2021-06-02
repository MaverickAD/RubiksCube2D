let Program = function()
{
    this.colorPalette = new ColorPalette();
};

Program.prototype.onClickColorPicker = function()
{
    $('#color-palette').fadeIn('slow');
};



// Gestionnaire d'évènement de changement de la couleur du crayon.
Program.prototype.onPickColor = function()
{
    var color;

    // Récupération de la couleur sur laquelle l'utilisateur a cliqué.
    color = this.colorPalette.getPickedColor();
    console.log(color);
    // Changement de la couleur du crayon.
    this.colorPalette.setColorAsRgb(color.red, color.green, color.blue);
    
    let box = document.querySelector("div#palette");
    box.style.backgroundColor = 'rgb(' + color.red + ',' + color.green + ',' + color.blue + ')';
    $('#color-palette').fadeOut('slow');
};


// Méthode appelée au démarrage de l'application.
Program.prototype.start = function()
{
    // Installation des gestionnaires d'évènements des outils.
    $('#tool-color-picker').on('click', this.onClickColorPicker.bind(this));


    // Création d'un évènement spécifique à l'application.
    $(document).on('magical-slate:pick-color', this.onPickColor.bind(this));
};