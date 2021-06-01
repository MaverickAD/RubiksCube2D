var clic = false;  
var clic2 = false;
var r = 255, g = 0, b = 0;
var r_1 = 255, g_1 = 0, b_1 = 0;
var blanc = 0, noir = 1;
var x = 360, y = 20;
var resultat_hexa;
  
function clique(objet) {
  if (objet == "barre") clic = true;
  else clic2 = true;
}
  
  
  function afficher() // ici on gère l'affichage de la couleur
  {
  
    noir = Math.round((x - 60) * 100 / 300) / 100;
    blanc = Math.round((y - 20) * 100 / 300) / 100;
  
    r_1 = Math.round((255 - r) * blanc) + r;
    g_1 = Math.round((255 - g) * blanc) + g;
    b_1 = Math.round((255 - b) * blanc) + b;
  
    r_1 = Math.round(r_1 * noir);
    g_1 = Math.round(g_1 * noir);
    b_1 = Math.round(b_1 * noir);
  
    // --modification--
  
    r_hexa = hexadecimal(Math.floor(r_1 / 16)) + hexadecimal(r_1 % 16);
    g_hexa = hexadecimal(Math.floor(g_1 / 16)) + hexadecimal(g_1 % 16);
    b_hexa = hexadecimal(Math.floor(b_1 / 16)) + hexadecimal(b_1 % 16);
  
   document.getElementById("resultat").value = "#" + r_hexa + g_hexa + b_hexa;
  
    // --fin modification--
  
  }
  
  
  
  // Et une nouvelle fonction
  
  function hexadecimal(nombre) {
  
    if (nombre < 10) {
      return nombre.toString(); // le nombre en chaîne de caractères.
    }
    else {
      var retour;
      switch (nombre) {
        case 10:
          retour = "A";
          break;
        case 11:
          retour = "B";
          break;
        case 12:
          retour = "C";
          break;
        case 13:
          retour = "D";
          break;
        case 14:
          retour = "E";
          break;
        case 15:
          retour = "F";
          break;
      }
      return retour;
    }
  
  }
  
  function position(axe, event) {
    // event contient les évènements de la page (on s'en sert pour la position du curseur)
  
    var e = event || window.event;
    // on copie les évènements dans e : il y a des manières différentes de récupérer les événements selon le navigateur
  
    if (axe == "x") //si on demande x
    {
      var rep = e.clientX; // position x de la souris.
    }
    else // sinon y 
    {
      var rep = e.clientY; // position y de la souris.
    }
  
    return rep;
    // on renvoie la valeur de rep.
  
  }
  
document.onmousedown = calcul;
  // lorsque la souris clique n'importe où dans le document, on appelle la fonction calcul.
  
document.onmouseup = function () { clic = false; clic2 = false; }
  // si l'utilisateur relâche le bouton de la souris, alors les variables clic et clic2 redeviennent fausses (false).
  
function calcul(event){
  
  if (clic && position('y', event) <= 320 && position('y', event) >= 20){
    document.getElementById("curseur1").style.top = position('y', event) - 7;
  
    if ((position('y', event) - 20) <= 50){
  
      r = 255;
      g = 0;
      b = Math.round((position('y', event) - 20) * 255 / 50);
    }
    else if ((position('y', event) - 20) <= 100){
      r = Math.round(255 - ((position('y', event) - 70) * 255 / 50));
      g = 0;
      b = 255;
    }
      else if ((position('y', event) - 20) <= 150) // 3/6 (150px)
      {
  
        r = 0;
        g = Math.round((position('y', event) - 120) * 255 / 50);
        b = 255;
  
      }
      else if ((position('y', event) - 20) <= 200) // 4/6 (200px)
      {
  
        r = 0;
        g = 255;
        b = Math.round(255 - ((position('y', event) - 170) * 255 / 50));
  
      }
      else if ((position('y', event) - 20) <= 250) // 5/6 (250px)
      {
  
        r = Math.round((position('y', event) - 220) * 255 / 50);
        g = 255;
        b = 0;
  
      }
      else if ((position('y', event) - 20) <= 300) // 6/6 (300px)
      {
  
        r = 255;
        g = Math.round(255 - ((position('y', event) - 270) * 255 / 50));
        b = 0;
  
      }
  
      document.getElementById("carre").style.backgroundColor = "rgb(" + r + "," + g + "," + b + ")";
      // On change la couleur du carré. On voit après (grâce à degrade n-b.png) le dégradé de la couleur vers le blanc et le noir.
  
      afficher(); // fonction permettant d'afficher la couleur courante dans le rectangle (input text) 'resultat'.
    }
  
    if (clic2) // si l'utilisateur clique sur le carré...
    {
      if (position('y', event) > 20 && position('y', event) < 320) {
        document.getElementById("curseur2").style.top = (position('y', event) - 10) + "px";
        // on déplace curseur2 et on lui retire son milieu (comme pour curseur 1)
  
        y = position('y', event);
        // on enregistre la position y de la souris dans la variable 'y' pour que la fonction afficher() puisse faire ces calculs.
      }
  
      if (position('x', event) > 60 && position('x', event) < 360) {
        document.getElementById("curseur2").style.left = (position('x', event) - 10) + "px";
        // on déplace curseur2 et on lui retire son milieu (comme pour curseur 1)
  
        x = position('x', event);
        // on enregistre la position x de la souris dans la variable 'x' pour que la fonction afficher() puisse faire ces calculs.
      }
  
      afficher(); // fonction permettant d'afficher la couleur courante dans le rectangle (input text) 'resultat'.
      resultat_hexa = "#" + r_hexa + g_hexa + b_hexa;
      var couleur = document.getElementsByClassName("skin_resultat")[0];
      console.log(couleur);
      couleur.style.background = resultat_hexa;
    }
  
  }
  
    function valider() {
    console.log(r);
    console.log(g);
    console.log(b);
  
    window.close();
    //on ferme la palette
  }

  function valider2() {
  
    window.close();
    //on ferme la palette
  }
  
  
  // on initialise 2 variables qui nous permettront d'envoyer la couleur dans le bon champ.
  
  champ = "";
  formulaire = "";
  
  function ouvrir_palette(formulaire_recupere, champ_recupere) {
  
    formulaire = formulaire_recupere;
    champ = champ_recupere;
  
    ma_palette = window.open("palette.html", "Palette_de_couleur", "height=380,width=400,status=0, scrollbars=0,menubar=0");
    // on ouvre la palette
  }
  
  function valid_couleur(couleur) //fonction appelée lorsqu'on valide la palette. On récupère la couleur.
  {
  
    document.forms[formulaire].elements[champ].value = couleur;
  
  }

