function toggleNav(){
    var navToggle = document.querySelector("div.nav-toggle");
    var nav = document.querySelector("nav.nav");
    var filter = document.querySelector("div.filter");
  
    navToggle.addEventListener('click', changeClassName(navToggle));
    nav.addEventListener('click', changeClassName(nav));
    filter.addEventListener('click', changeClassName(filter));
  }
  
  function changeClassName(e){
    e.classList.toggle("expanded");
  }