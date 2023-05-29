const switchGeneral = document.getElementById("general");

const ip = "http://192.168.61.88:80/";

switchGeneral.addEventListener("change", function() {
  if (this.checked) {

    fetch(ip+'encender', {
    })
    .then(function(response) {
      if (response.ok) {
        console.log('Botón activado correctamente');
      } else {
        console.log('Error al activar el botón');
      }
    })
    .catch(function(error) {
      console.log('Error en la solicitud HTTP:', error.message);
    });

  } else {

      fetch(ip+'apagar', {
      })
      .then(function(response) {
        if (response.ok) {
          console.log('Botón activado correctamente');
        } else {
          console.log('Error al activar el botón');
        }
      })
      .catch(function(error) {
        console.log('Error en la solicitud HTTP:', error.message);
      });

  }
});

const switchServo = document.getElementById("servo");

switchServo.addEventListener("change", function() {
  if (this.checked) {

    fetch(ip+'servo', {
    })
    .then(function(response) {
      if (response.ok) {
        console.log('Botón activado correctamente');
      } else {
        console.log('Error al activar el botón');
      }
    })
    .catch(function(error) {
      console.log('Error en la solicitud HTTP:', error.message);
    });

  } else {

      fetch(ip+'servoOff', {
      })
      .then(function(response) {
        if (response.ok) {
          console.log('Botón activado correctamente');
        } else {
          console.log('Error al activar el botón');
        }
      })
      .catch(function(error) {
        console.log('Error en la solicitud HTTP:', error.message);
      });

  }
});

const switchAlarma = document.getElementById("alarma");

switchAlarma.addEventListener("change", function() {
  if (this.checked) {

    fetch(ip+'alarma', {
    })
    .then(function(response) {
      if (response.ok) {
        console.log('Botón activado correctamente');
      } else {
        console.log('Error al activar el botón');
      }
    })
    .catch(function(error) {
      console.log('Error en la solicitud HTTP:', error.message);
    });

  } else {

      fetch(ip+'alarmaOff', {
      })
      .then(function(response) {
        if (response.ok) {
          console.log('Botón activado correctamente');
        } else {
          console.log('Error al activar el botón');
        }
      })
      .catch(function(error) {
        console.log('Error en la solicitud HTTP:', error.message);
      });

  }
});

const switchLed = document.getElementById("led");

switchLed.addEventListener("change", function() {
  if (this.checked) {

    fetch(ip+'led', {
    })
    .then(function(response) {
      if (response.ok) {
        console.log('Botón activado correctamente');
      } else {
        console.log('Error al activar el botón');
      }
    })
    .catch(function(error) {
      console.log('Error en la solicitud HTTP:', error.message);
    });

  } else {

      fetch(ip+'ledOff', {
      })
      .then(function(response) {
        if (response.ok) {
          console.log('Botón activado correctamente');
        } else {
          console.log('Error al activar el botón');
        }
      })
      .catch(function(error) {
        console.log('Error en la solicitud HTTP:', error.message);
      });

  }
});

