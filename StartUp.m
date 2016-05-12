%ansluter sig till arduino-kortet
s = serial('COM13', 'BAUDRATE', 115200)

%Öppnar porten
set(s, 'Terminator', 10);
fopen(s);

%Pausar i 4 sekunder och flushar in och utgång 
%så att inga gamla värdet är kvar
pause(4);
flushinput(s);
flushoutput(s);

%Här skickar vi vårt första värde t
fwrite(s, uint8(5))

%PID-variablerna. Vi dividerar dom med 100 i atmel för att få ut de riktiga
%värdena
temp=0;
kp = 090; 
Td = 033;
Ti = 160;
borvarde = 25;


temp=fscanf(s);
disp(temp);


%Skickar KP-värdet och får tillbaka en verifiering
fwrite(s, uint8(kp))
temp=fscanf(s);
disp('Kp=');
disp(temp);

%Skickar TI värdet och får tillbaka en verifiering
fwrite(s, uint8(Ti))
temp=fscanf(s);
disp('Ti=');
disp(temp);

%Skickar Td värdet och får tillbaka en verifiering
fwrite(s, uint8(Td))
temp=fscanf(s);
disp('Td=');
disp(temp)

% Här skickar vi börvärdet och får tillbaka en verifiering
fwrite(s, uint8(borvarde))  
temp=fscanf(s);
disp('Bv=');
disp(temp);

