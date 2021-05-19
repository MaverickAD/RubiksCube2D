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
    console.log(target)
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

var dgReadMoreText1 = "V";
var dgReadMoreText2 = "˄";

function dgReadMore(id) {
  var dots = document.getElementById("dg-rm-dots-"+id);
  var moreText = document.getElementById("dg-rm-more-"+id);
  var btnText = document.getElementById("dg-rm-btn-"+id);
  console.log(dots)
  if (dots.style.display === "none") {
    dots.style.display = "inline";
    btnText.innerHTML = dgReadMoreText1;
    moreText.style.display = "none";
  } else {
    dots.style.display = "none";
    btnText.innerHTML = dgReadMoreText2;
    moreText.style.display = "inline";
  }
  window.scrollTo(0, 0);
}