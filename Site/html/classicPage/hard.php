<?php

if (array_key_exists("Pseudo", $_POST)) {
    $Pseudo = htmlspecialchars($_POST["Pseudo"]);

    // 1 : on ouvre le fichier
    $monfichier = fopen('../../leaderboard/leaderboardHard.txt', 'a+'); 
    fputs($monfichier, $Pseudo.";\n"); 

    // 3 : quand on a fini de l'utiliser, on ferme le fichier
    fclose($monfichier);
}

?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Page Hard</title>
    <link rel="stylesheet" href="../../css/allCSSPage/CSSAllPages.css">
    <link rel="stylesheet" href="../../css/adventurePage/CSSAdventurePage1.css">
    <link rel="icon" type="image/png" sizes="16x16" href="../../img/logo.png">
    <script src="https://kit.fontawesome.com/65f54486e0.js" crossorigin="anonymous"></script>
</head>

<body>
    <div class="nav-toggle" onclick="toggleNav()">
        <div class="nav-toggle-bar"></div>
    </div>
    <nav class="nav">
        <ul>
            <li><a href="../adventurePage/adventure1.html" id="navBar_adventureTitle" onclick="toggleNav()">Adventure mode</a></li>
            <li><a href="../classic_mode.html" id="navBar_classicTitle" onclick="toggleNav()">Classic mode</a></li>
            <li><a href="../maker.html" id="navBar_makerTitle" onclick="toggleNav()">Maker mode</a></li>
            <li><a href="../../index.html" id="navBar_instruction" onclick="toggleNavInstruction()">Instruction</a></li>
            <li><a href="#" id="navBar_darkMode" onclick="darkMode()">Dark mode</a></li>
        </ul>
    </nav>
    <div class="filter" id="blur">
        <header>
            <div id="mainTitle">
                <img src="../../img/logo.png" alt="logo" width="100">
                <h1><a href="../../index.html">Rubik's Cube 2D</a></h1>
            </div>
        </header>

        <main id="classic-main-mod">
            <div id="info-mod-shuffle">
                <div id="mod"><h3>Hard</h3></div>
                <div id="shuffle"></div>
            </div>

            <div id="ligne-jeu">
            <div id="popup">
                    <div class="half-box1">
                        <h2>Good game, you succeed</h2>
                    </div>
                    <div class="half-box2">
                        <div class="half-half-box1">
                            <p>Your score :</p>
                            <p>Your time:</p>
                            <form action="hard.php" method="post">
                                <TR><TD>Pseudo :</TD><TD><INPUT Type="Text" NAME="Pseudo" ID="Pseudo"></INPUT></TD></TR>
                                <input type="submit" value="Envoyer" />
                                </form>
                        </div>
                        <div class="half-half-box2">
                            
                            <div class="half-half-half">
                                <a href="">
                                    <div class="text">
                                        <p>Restart</p>
                                    </div>
                                </a>
                            </div>
                            
                        </div>
                    </div>
                </div>

                <div id="boite-pattern">

                    <div id="petite-boite-pattern">
                        <div id="wrapper-witness">
                            <div class="box" id="witness"></div>
                        </div>
                    </div>
                </div>

                <div id="boite-jeu">
                    <div class="box" id="top">
                        <div id="cornerTopLeft"></div>
                        <div class="box" id="buttonsTop"></div>
                        <div id="cornerTopRight"></div>
                    </div>
                    <div class="box" id="middle">
                        <div class="box" id="buttonsLeft"></div>
                        <div class="box" id="game"></div>
                        <div class="box" id="buttonsRight"></div>
                    </div>
                    <div class="box" id="bottom">
                        <div id="cornerBottomLeft"></div>
                        <div class="box" id="buttonsBottom"> </div>
                        <div id="cornerBottomRight"></div>
                    </div>
                </div>

                <div id="leaderboard">
                    <div id="timer">TIMER : 
                        <div id="chronotime">0:00:00,00</div>
                        <form name="chronoForm">
                        </form>
                    </div>
                    <div id="petit-leaderboard">LEADERBOARD</div>
                </div>

            </div>
        </main>

        <footer>
            <p>&copy;ISEN_Project_CIR1_2021 by TeamName</p>
        </footer>
    </div>
    <script src="../../js/classicPage/hard.js"></script>
    <script src="../../js/JSChrono.js"></script>
    <script src="../../js/JSToggleNav.js"></script>
</body>

</html>