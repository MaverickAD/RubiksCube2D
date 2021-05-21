function darkMode(){
  var body = document.querySelector("body");
  console.log(body);
  body.classList.toggle("dark-mode")
}

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

window.smoothScroll = function(target) {
  var scrollContainer = target;
  do { //find scroll container
      scrollContainer = scrollContainer.parentNode;
      if (!scrollContainer) return;
      scrollContainer.scrollTop += 1;
  } while (scrollContainer.scrollTop == 0);

  var targetY = 0;
  do { //find the top of target relatively to the container
      if (target == scrollContainer) break;
      targetY += target.offsetTop;
  } while (target = target.offsetParent);

  scroll = function(c, a, b, i) {
      i++; if (i > 30) return;
      c.scrollTop = a + (b - a) / 30 * i;
      setTimeout(function(){ scroll(c, a, b, i); }, 20);
  }
  // start scrolling
  scroll(scrollContainer, scrollContainer.scrollTop, targetY, 0);
}


var open = false;

function dgReadMore(id) {
  var dots = document.getElementById("dg-rm-dots-" + id);
  var moreText = document.getElementById("dg-rm-more-" + id);
  if (open === false) {
    if (dots.style.display === "none") {
      dots.style.display = "inline";
      moreText.style.display = "none";
    } else {
      dots.style.display = "none";
      moreText.style.display = "flex";
      moreText.style.flexDirection = "row";
      moreText.style.flexWrap = "wrap";
      moreText.style.justifyContent = "space-around";
      open = true;
    }
  }
  
  smoothScroll(moreText);
}

var i = 0;

function color() {
  var colorTab = ["#009B48", "#B90000", "#0045AD", "#FF5900", "#FFFFFF", "#FFD500"];
  var block = document.querySelector('div#playBlock');
  block.style.background = colorTab[i];
  i++;
  if (i === 6) { i = 0 }
}

function removeColor() {
  var block = document.querySelector('div#playBlock');
  block.style.background = "";
}

function toggleNavInstruction(){
  toggleNav();
  dgReadMore('1');
}