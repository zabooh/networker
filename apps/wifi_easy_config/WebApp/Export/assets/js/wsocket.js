
console.log('Document ready');
           
var serverIP = window.location.hostname;          
var m_connect = document.getElementById('m_connect');
var m_disconnect = document.getElementById('m_disconnect');
var m_send_text = document.getElementById('m_send_text');
var m_send_button = document.getElementById('m_send_button');
var wsServer = document.getElementById('wsServer');
var tempButton = document.getElementById('tempButton');//added 
var tempValue = document.getElementById('tempValue');//added 
var myChart = document.getElementById('myChart');
var myTrigger = document.getElementById('myTrigger');

// Daten initialisieren
var t_data = [];
var y_data =   [];

var totalPoints = 100;

for (ix = 0; ix < totalPoints; ix++) {
    t_data.push(ix)
    y_data.push(0);
}

// Chart.js-Objekt erstellen
var ctx = document.querySelector('#myChart canvas').getContext('2d');

var myChart_2 = new Chart(ctx, {
  
  type: 'line',
  
 options: {
      scales: {
        x: {
          type: 'linear', // Art der Skalierung für die x-Achse
          display: true,
          scaleLabel: {
            display: true,
            labelString: 'X-Achse'
          }
        },
        y: {
          type: 'linear', // Art der Skalierung für die y-Achse
          display: true,
          scaleLabel: {
            display: true,
            labelString: 'Y-Achse'
          }
        }
      }
    },


 
  data: {
    labels: t_data,
    datasets: [{
      label: 'Data From yC',
      data: y_data,
      backgroundColor: 'rgba(54, 162, 235, 0.2)',
      borderColor: 'rgba(54, 162, 235, 1)',
      borderWidth: 1
    }]
  },
  
  
  
});
    
console.log("Die IP-Adresse des Servers lautet: " + serverIP);
wsServer.value = "ws://" + serverIP + ":8000" + "/echo"

m_connect.disabled = false;
m_disconnect.disabled = true; 
m_send_text.disabled = true; 
m_send_button.disabled = true; 
wsServer.disabled = false;

var xx=0;
var yy=0;

myTrigger.addEventListener('click', function(event) {
    console.log('myTrigger Clicked');

    t_data.slice(1);
    y_data.slice(1);

    t_data.push(xx);
    y_data.push(yy);
    
    xx++;
    yy++;
    
    // Daten im Chart aktualisieren
    myChart_2.data.labels = t_data;
    myChart_2.data.datasets[0].data = y_data;
    myChart_2.update();
    
});

tempButton.addEventListener('click', function(event) {
    console.log('tempButton Clicked');
	
	     let message =
         '{"Control":"Temperature"}' 
                
        ws.send(message);        
        console.log('Message Send: '+ message);
    
});

m_connect.addEventListener('click', function(event) {
    
    ws = new WebSocket( wsServer.value );
    console.log('Connect Clicked');

    m_disconnect.addEventListener('click', function(event) {
        m_connect.disabled = false;
        m_disconnect.disabled = true;
        ws.close();
        console.log('Disconnect Clicked');
    });

    m_send_button.addEventListener('click', function(event) {
        //var message = m_send_text.value;
                        
        let var1 = 'peng'
        let var2 = m_send_text.value
        let var3 = 3
        let var4 = 'peng'
        let var5 = 'blöd'
        let var6 = 'warum'

        let message =
         '{"var1":"' + var1 + '","var2":"' + var2 + '",' +         
          '"var3":'  + var3 +  ',"var4":"' + var4 + '",' +
          '"var5":"' + var5 + '","var6":"' + var6 + '"}' 
                
        ws.send(message);        
        console.log('Message Send: '+ message);
    });
    
    ws.onopen = function() {
        m_connect.disabled = true;
        m_disconnect.disabled = false;         
        m_send_text.disabled = false; 
        m_send_button.disabled = false;
        wsServer.disabled = true;
        console.log('WebSocket opened');
    };    

    ws.onmessage = function(event) {
        const received = event.data;
        console.log('WebSocket message receive ' + received);                
        const obj = JSON.parse(received); 
        console.log('var1:'+obj.var1);
        console.log('var2:'+obj.var2);
        console.log('var3:'+obj.var3);
        console.log('var4:'+obj.var4);
        console.log('var5:'+obj.var5);
        console.log('var6:'+obj.var6);    	
		console.log('Temperature:'+obj.Temperature);
		tempValue.value = obj.Temperature;
		
    };
                    
    ws.onclose = function() {  
        m_connect.disabled = false;
        m_disconnect.disabled = true;
        m_send_text.disabled = true; 
        m_send_button.disabled = true;
        wsServer.disabled = false;
        console.log('WebSocket closed');
    };
    
    
});


