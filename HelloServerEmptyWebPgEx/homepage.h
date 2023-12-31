// To create literal strings stored in flash memory enclose your HTML code between 
// F(R"=====( HTML code here )=====");
// If you have 1 reading then you probably have 2 literal strings
// If you have 2 readings then you probably have 3 literal strings etc.

String homePagePart1 = F(R"=====(
<!DOCTYPE HTML>
<html lang="en">
<head>
    <title>IOT Project - Andrew Fox</title>
    <style type="text/css">


* {
    margin: 5;
    padding: 0;
    box-sizing: border-box;
}

body {
    height: 100vh;
    background: #FFF;
    font-family: "Roboto", sans-serif;
}

nav {
    box-shadow:
  2.8px 2.8px 2.2px rgba(0, 0, 0, 0.02),
  6.7px 6.7px 5.3px rgba(0, 0, 0, 0.028),
  12.5px 12.5px 10px rgba(0, 0, 0, 0.035),
  22.3px 22.3px 17.9px rgba(0, 0, 0, 0.042),
  41.8px 41.8px 33.4px rgba(0, 0, 0, 0.05),
  100px 100px 80px rgba(0, 0, 0, 0.07)
;
    border-radius: 15px;  
    display: flex;
    justify-content: space-between;
    padding: 15px 5%;
    align-items: center;
    background: #18283B;
}

.logo {
    color: #FFF;
    font-size: 22px;
}

ul {
    list-style: none;
}

ul li {
    display: inline-block;
}

ul li a {
    text-decoration: none;
    color: #8291A5;
    padding: 8px 30px;
    border-radius: 7px;
    transition: all .3s ease;
}

ul li a:hover,
ul li a.active {
    color: #FFF;
    background: #0075FF;
}

#icon {
    background-color: #0075FF;
    padding: 5px 7px 3px 7px;
    border-radius: 4px;
    cursor: pointer;
    transition: all .3s ease;
}

#icon svg {
    color: #FFF;
    height: 28px;
    transition: all .3s ease;
}

#icon:hover {
    background: #FFF;
}

#icon:hover svg {
    color: #0075FF;
}

#checkbox,
#icon {
    display: none;
}





/****************************/


.box {
  box-shadow:
  0 2.8px 2.2px rgba(0, 0, 0, 0.034),
  0 6.7px 5.3px rgba(0, 0, 0, 0.048),
  0 12.5px 10px rgba(0, 0, 0, 0.06),
  0 22.3px 17.9px rgba(0, 0, 0, 0.072),
  0 41.8px 33.4px rgba(0, 0, 0, 0.086),
  0 100px 80px rgba(0, 0, 0, 0.12)
;

  
  
  min-height: 200px;
  width: 50vw;
  margin: 100px auto;
  background: white;
  border-radius: 5px;
}





    </style>
</head>
<body>
    <nav>
        <div class="logo">Internet of Things Project - Andrew Fox</div>
        <input type="checkbox" id="checkbox">
        <label for="checkbox" id="icon">
            <svg fill="none" stroke="currentColor" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M4 6h16M4 12h16M4 18h16"></path></svg>
        </label>
        <ul>
            <li><a href="#" class="active">Home</a></li>
            <li><a href="#">About</a></li>
            <li><a href="#">Project</a></li>
            <li><a href="#">Login</a></li>
        </ul>
    </nav>

    <div class="box">

            <iframe width="560" height="560" src="http://192.168.1.10:81/stream"></iframe>
         <p style="text-align: center;">
        </p>
    </div>
</body>
</html>
)=====");
