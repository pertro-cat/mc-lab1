#ifndef INDEX_HTML_H
#define INDEX_HTML_H

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>

<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        body {
            font-family: Arial;
            text-align: center;
            margin: 0px auto;
            padding-top: 30px;
        }

        .button {
            padding: 10px 20px;
            font-size: 24px;
            text-align: center;
            outline: none;
            color: #fff;
            background-color: #2f4468;
            border: none;
            border-radius: 5px;
            box-shadow: 0 6px #999;
            cursor: pointer;
            -webkit-tap-highlight-color: rgba(0, 0, 0, 0);
        }

        .button:hover {
            background-color: #1f2e45
        }

        .button:active {
            background-color: #1f2e45;
            box-shadow: 0 4px #666;
            transform: translateY(2px);
        }

        .leds {
            width: 100px;
            height: 100px;
            margin: 20px;
            display: inline-block;
            border: 5px solid black;
            border-radius: 50%;
        }

        .container {
            text-align: center;
        }

        #led1 {
            background-color: white;
        }

        @media screen and (max-width: 480px) {
            .leds {
                width: 50px;
                height: 50px;
            }

            .button {
                padding: 15px 100px 15px 10px;
                font-size: 10px;
            }

            h1 {
                font-size: 24px;
                padding-top: 20px;
            }
        }
    </style>
</head>

<body>
    <h1>ESP Pushbutton Web Server</h1>
    <!-- onmousedown / onmouseup - on PC/Laptop, ontouchend / ontouchstart - on mobile -->
<button class="button" onclick="algorighm1();">Algo 1</button>
<button class="button" onclick="algorighm2();">Algo 2</button>

<div class="container">
    <h2>Blink blink</h2>
    <div id="led1" class="leds"></div>
    <div id="led2" class="leds"></div>
    <div id="led3" class="leds"></div>
</div>





<script>
        var led1 = document.getElementById('led1');
        var led2 = document.getElementById('led2');
        var led3 = document.getElementById('led3');



        function toggleCheckLed1(element) {
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "/status_led_1", true);
            xhr.onreadystatechange = function () {
                if (xhr.readyState === 4 && xhr.status === 200) {
                    var status_led_1 = xhr.responseText;
                    console.log("Led1 status:", status_led_1);
                    if (status_led_1 === '1') {
                        led1.style.backgroundColor = 'red';
                    } else {
                        led1.style.backgroundColor = 'white';
                    }
                }
            };
            xhr.send();
        }

        function toggleCheckLed2(element) {
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "/status_led_2", true);
            xhr.onreadystatechange = function () {
                if (xhr.readyState === 4 && xhr.status === 200) {
                    var status_led_2 = xhr.responseText;
                    console.log("Led2 status:", status_led_2);

                    if (status_led_2 === '1') {
                        led2.style.backgroundColor = 'green';
                    } else {
                        led2.style.backgroundColor = 'white';
                    }
                }
            };
            xhr.send();
        }

        function toggleCheckLed3(element) {
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "/status_led_3", true);
            xhr.onreadystatechange = function () {
                if (xhr.readyState === 4 && xhr.status === 200) {
                    var status_led_3 = xhr.responseText;
                    console.log("Led3 status:", status_led_3);
                    if (status_led_3 === '1') {
                        led3.style.backgroundColor = '#ffff99';
                    } else {
                        led3.style.backgroundColor = 'white';
                    }
                }
            };
            xhr.send();
        }

        setInterval(toggleCheckLed1, 50);
        setInterval(toggleCheckLed2, 50);
        setInterval(toggleCheckLed3, 50);


    let isOn1 = false;
    function algorighm1() {
        isOn1 = !isOn1; 
        var xhr = new XMLHttpRequest();
        xhr.open("GET", isOn1 ? "/on_alg1" : "/off_alg1", true);
        xhr.send();
    }

    let isOn2 = false;
    function algorighm2() {
        isOn2 = !isOn2; 
        var xhr = new XMLHttpRequest();
        xhr.open("GET", isOn2 ? "/on_alg2" : "/off_alg2", true);
        xhr.send();
    }
    </script>
</body>

</html>

</html>
    )rawliteral";

#endif