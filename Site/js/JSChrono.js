'use strict';
let timer = null;
let hh = 0; // heures
let mm = 0; // Minutes
let ss = 0; // Secondes
let cs = 0; // Centièmes de secondes

function ajouter() {
  //console.log(ss);
  // Incrémenter les centièmes de seconde
  cs++;
  // Incrémentation des secondes
  if (cs > 99) {
    ss++;
    cs = 0;
  }
  // Incrémentation des minutes
  if (ss > 59) {
    mm++;
    ss = 0;
  }
  // Incrémentation des heures
  if (mm > 59) {
    hh++;
    mm = 0;
  }
  afficherChrono(hh, mm, ss, cs);
}

function format_number(number) {
  // Formatage du nombre sur 2 chiffres
  return ("0" + number).slice(-2);
}

function afficherChrono(hh, mm, ss, cs) {
  document.getElementById('chronotime').innerHTML = hh+':'+format_number(mm)+':'+format_number(ss)+','+format_number(cs);
}

function chronoStartStop() {
  if (timer == null) {
    chronoStart()
  }
  else {
    chronoStop();
  }
}

function chronoStart() {
  //console.log('Chrono start');
  timer = window.setInterval(ajouter, 10);
}

function chronoReset() {
  console.log('Chrono reset');
  hh = 0;
  mm = 0;
  ss = 0;
  cs = 0;
  chronoStart();
  afficherChrono(hh, mm, ss, cs);
}

document.addEventListener("DOMContentLoaded",function() {
  // Définition des variables bouton
  var btnStart = document.getElementById('button_shuffle');
  var btnReset = document.getElementById('button_shuffle');
  // Ajout des écouteurs d'événements sur les boutons
	btnStart.addEventListener('click', chronoStartStop);
  btnReset.addEventListener('click', chronoReset);
});

function chronoStop() {
    //console.log('Chrono stop');
    window.clearInterval(timer);
    timer = null;
  }