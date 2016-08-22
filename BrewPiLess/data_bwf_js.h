const char data_bwf_js[] PROGMEM =
R"END(
function invoke(b){var c=new XMLHttpRequest();c.onreadystatechange=function(){if(c.readyState==4){if(c.status==200){b.success(c.responseText)}else{c.onerror(c.status)}}};c.ontimeout=function(){if(typeof b["timeout"]!="undefined")b.timeout();else c.onerror(-1)},c.onerror=function(a){if(typeof b["fail"]!="undefined")b.fail(a)};c.open(b.m,b.url,true);if(typeof b["data"]!="undefined"){c.setRequestHeader("Content-Type",(typeof b["mime"]!="undefined")?b["mime"]:"application/x-www-form-urlencoded");c.send(b.data)}else c.send()}var BWF={BrewProfile:"/brewing.json",sse:true,process:function(a){if(this.raw!=null){this.raw(a);return}eval("m={"+a+"}");for(var b in m){if(typeof this.handlers[b]!="undefined"){this.handlers[b](m[b])}}},on:function(a,b){this.handlers[a]=b},send:function(a,c){c=(typeof c=="undefined")?{}:c;var b=this;b.ws.send(a)},connect:function(){var b=this;b.ws=new WebSocket('ws://'+document.location.host+'/websocket');b.ws.onopen=function(){console.log("Connected");b.onopen()};b.ws.onclose=function(){console.log("Disconnected");setTimeout(function(){b.connect()},1500);b.onclose()};b.ws.onerror=function(e){console.log("ws error",e);b.error(e)};b.ws.onmessage=function(e){b.process(e.data)}},init:function(a){var b=this;this.error=(typeof a.error=="undefined")?function(e){alert("error:"+e)}:a.error;this.handlers=(typeof a.handlers=="undefined")?{}:a.handlers;this.raw=(typeof a.raw=="undefined")?null:a.raw;this.onopen=(typeof a.onopen=="undefined")?function(){}:a.onopen;this.onclose=(typeof a.onclose=="undefined")?function(){console.log("connection close")}:a.onclose;if(typeof WebSocket==="undefined"){console.log("not support S");alert("WebSocket not Supporte");return}b.connect()},save:function(a,b,c,d){invoke({m:"POST",url:"/fputs",data:"path="+a+"&content="+b,success:function(){c()},fail:function(e){d(e)}})},load:function(a,b,c){invoke({m:"GET",url:a,success:function(d){b(d)},fail:function(e){c(e)}})}};
)END";