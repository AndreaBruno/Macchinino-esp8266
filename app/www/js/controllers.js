angular.module('starter.controllers', [])


.controller('AppCtrl', function($scope, $state, $location, $ionicModal) {
    ionic.Platform.ready(function() {
        console.log("pronto");
        udptransmit.initialize("192.168.4.1", 5000);
    });

    $scope.udpInit = function(ip, port) {
        function UDPTransmitterInitializationSuccess(success) {
            console.log(success);
        }

        function UDPTransmitterInitializationError(error) {
            console.log(error);
        }
        udptransmit.initialize(ip, port);
    };

    $scope.udpSend = function(msg) {
        function UDPTransmissionSuccess(success) {
            console.log("inviato");
        }

        function UDPTransmissionError(error) {
            console.log("errore invio");
        }
        udptransmit.sendMessage(msg);
    };
})

.controller('HomeCtrl', function($scope, $stateParams) {
    ionic.Platform.ready(function() {
        console.log("Home");
        $scope.udpInit("192.168.4.1", 5000);
        var xCoord = 5;
        var yCoord = 5;
        var widthCenter = window.innerWidth / 2;
        var heigthCenter = (window.innerHeight - 44) / 2;

        console.log("widthCenter: " + widthCenter + " --- heigthCenter: " + heigthCenter);


        var pippo = document.getElementById("allcontent");
        pippo.addEventListener('touchmove', function(e) {
            var touch = event.touches[0];
            var x = Math.round(touch.pageX);
            var y = Math.round(touch.pageY);

            console.log("x: " + x + " --- y: " + y);

            xCoord = Math.round((x * 9) / window.innerWidth);
            yCoord = Math.round((y * 9) / (window.innerHeight - 44));

            if (xCoord == 10) xCoord = 9;
            if (yCoord == 10) yCoord = 9;

            console.log("x: " + xCoord + " --- y: " + yCoord);
        });
        pippo.addEventListener('touchstart', function(e) {
            console.log("start");
        });
        pippo.addEventListener('touchend', function(e) {
            xCoord = 5;
            yCoord = 5;
            console.log("end");
        });

        var myVar = setInterval(function() {
            myTimer()
        }, 200);

        function myTimer() {
            var dataToSend = "A" + xCoord + "D" + yCoord;
            console.log("dataToSend: " + dataToSend);

            try {
                $scope.udpSend(dataToSend);
            } catch(e) {}
        }

        //$scope.udpInit("192.168.4.1", 5000);
        //$scope.udpSend("pippo");
    });

});