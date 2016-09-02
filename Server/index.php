<?php
  if(isset($_POST['cmd'])) {
    $string = implode("", $_POST['cmd']);
    if(is_numeric($string))
      file_put_contents("cmd.txt", $string);
  }
?>
<head>
  <script src="https://code.jquery.com/jquery-2.2.3.js" integrity="sha256-laXWtGydpwqJ8JA+X9x2miwmaiKhn8tVmOVEigRNtP4=" crossorigin="anonymous"></script>
 <link href="https://fonts.googleapis.com/icon?family=Material+Icons"
      rel="stylesheet">
  <style>
    body {
      background:gray;
      margin:20px;
      margin-top:40px;
    }
  #forward {
    background: #3C3B3B;
    color: yellow;
    padding: 10px;
    border-top-left-radius: 6px;
    border-top-right-radius: 6px;
    display: inline-block;
    border: 1px solid gray;
    box-shadow: 0px 0px 10px black;
}
    #stop {
      background: #3C3B3B;
    color: yellow;
    padding: 10px;
    display: inline-block;
    border: 1px solid gray;
    box-shadow: 0px 0px 10px black;
    }
     #backward {
    background: #3C3B3B;
    color: yellow;
    padding: 10px;
    border-bottom-left-radius: 6px;
    border-bottom-right-radius: 6px;
    display: inline-block;
    border: 1px solid gray;
    box-shadow: 0px 0px 10px black;
}
    
      #left {
    background: #3C3B3B;
    color: yellow;
    padding: 10px;
    border-top-left-radius: 6px;
    border-bottom-left-radius: 6px;
    display: inline-block;
    border: 1px solid gray;
    box-shadow: 0px 0px 10px black;
        margin-right:0px;
}      #right {
    background: #3C3B3B;
    color: yellow;
    padding: 10px;
    border-top-right-radius: 6px;
    border-bottom-right-radius: 6px;
    display: inline-block;
    border: 1px solid gray;
    box-shadow: 0px 0px 10px black;
  margin-left:0px;
}
    .motor_control {
          display: inline-block;
    width: 45px;
      cursor:pointer;
      margin-right:300px;
    }
  </style>
</head>

<form id="form" method="POST">
  <div class="motor_control">
  <div id="forward">
    <i class="material-icons">keyboard_arrow_up</i>
  </div>
  <div id="stop">
    <i class="material-icons">pause</i>
  </div>
  <div id="backward">
          <i class="material-icons">keyboard_arrow_down</i>  
  </div>
  </div>
  <div class="motor_control" style="width: 98px;margin:0px;">
  <div id="left">
    <i class="material-icons">keyboard_arrow_left</i>
  </div>
  <div id="right">
        <i class="material-icons">keyboard_arrow_right</i>
  </div>
  </div><input type="hidden" value=0 name="cmd[]" id="motor1">
  <input type="hidden" value=0 name="cmd[]" id="motor2">
  <script>
    function submitForm() {
          $.ajax({
           type: "POST",
           url: 'http://gharbi.me/arduinorc/index.php',
           data: $("#form").serialize()
         });

    }
  $('#forward').click(function() {
    $('#motor1').val(1);
    $('#motor2').val(1);
    submitForm();
  });
  $('#stop').click(function() {
    $('#motor1').val(0);
    $('#motor2').val(0);
    submitForm();
  });
      $('#backward').click(function() {
    $('#motor1').val(2);
    $('#motor2').val(2);
    submitForm();
  });
  $('#right').click(function() {
    $('#motor1').val(1);
    $('#motor2').val(2);
    submitForm();
  });
    
  $('#left').click(function() {
    $('#motor1').val(2);
    $('#motor2').val(1); 
    submitForm();
  });
  </script>
</form>