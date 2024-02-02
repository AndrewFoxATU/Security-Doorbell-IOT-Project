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
    padding: 0;
    box-sizing: border-box;
}

.header {
  padding: 30px;
  text-align: center;
  color: #FFF;
  font-size: 40px;

}

body {
    margin: 0;
    min-height: 100vh;
    background-color: #0075FF;
    font-family: "Roboto", sans-serif;
}

nav {
    margin: 0 1%;
    box-shadow: rgba(0, 0, 0, 0.25) 0px 54px 55px, rgba(0, 0, 0, 0.12) 0px -12px 30px, rgba(0, 0, 0, 0.12) 0px 4px 6px, rgba(0, 0, 0, 0.17) 0px 12px 13px, rgba(0, 0, 0, 0.09) 0px -3px 5px;;
    border-radius: 15px;
    display: flex;
    justify-content: space-between;
    padding: 15px 5%;
    align-items: center;
    background: #18283B;
    width: 98%;
    transition: ease-in-out .5s;
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




.sticky {
  position: fixed;
  top: 0;
  width: 100%;
  margin: 0;
  border-radius: 0px;
  transition: ease-in-out .5s;
}

.sticky + .box {
  margin-top: 183px;

}
/*******************************/
        .box {
            box-shadow: rgba(0, 0, 0, 0.25) 0px 54px 55px, rgba(0, 0, 0, 0.12) 0px -12px 30px, rgba(0, 0, 0, 0.12) 0px 4px 6px, rgba(0, 0, 0, 0.17) 0px 12px 13px, rgba(0, 0, 0, 0.09) 0px -3px 5px;
            text-align: center;
            width: 66vw; /* Adjust as needed for the desired aspect ratio */
            height: 37.125vw; /* 16:9 aspect ratio (width / 16 * 9) */
            max-width: 100%;
            margin: 100px auto;
            background: white;
            border-radius: 30px;
        }

    .motion-status {
        text-align: center;
        margin-top: 20px; /* Adjust as needed for spacing */
    }

    #motionStatus {
        font-size: 24px; /* Adjust as needed for font size */
      
        font-weight: bold; /* Add if you want bold text */
        margin-bottom: 10px; /* Adjust as needed for spacing */
    }

    </style>
</head>
<body>
    <div class="header">
        <h2>Smart Security Doorbell</h2>
        <p></p>
    </div>
    <nav id="navbar">
        <div class="logo">Internet of Things Project - Andrew Fox</div>
        <input type="checkbox" id="checkbox">
        <label for="checkbox" id="icon">
            <svg fill="none" stroke="currentColor" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg">
                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M4 6h16M4 12h16M4 18h16"></path>
            </svg>
        </label>
        <ul>
            <li><a href="#" class="active">Home</a></li>
            <li><a href="#">About</a></li>
            <li><a href="#">Video</a></li>
            <li><a href="Login.html">Login</a></li>
        </ul>
    </nav>

    <div class="box">
        <iframe style="border-radius: 30px; width: 100%; height: 100%;" src="http://172.20.10.4:81/stream"></iframe>
    </div>

    <div class="motion-status">
        <p id='motionStatus'>No Motion Detected</p>
    </div>

    <h1>
        
    </h1>

    <script>
        window.onscroll = function () {
            myFunction()
        };

        var navbar = document.getElementById("navbar");
        var sticky = navbar.offsetTop;

        function myFunction() {
            if (window.pageYOffset >= sticky) {
                navbar.classList.add("sticky")
            } else {
                navbar.classList.remove("sticky");
            }
        }

        // Function to update motion status on the webpage
        function updateMotionStatus(status) {
            document.getElementById('motionStatus').innerHTML = status;
        }

        // Periodically update the motion status every 2.5 second (2500 milliseconds)
        setInterval(function () {
            // Use AJAX to request the latest motion status from the server
            var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function () {
                if (xhr.readyState == 4 && xhr.status == 200) {
                    eval(xhr.responseText); // Execute the JavaScript code received from the server
                }
            };
            xhr.open('GET', '/motion-status', true);
            xhr.send();
        }, 2500); // 2500 milliseconds = 2.5 second
    </script>
</body>
</html>

)=====");
