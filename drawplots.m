% Antalet värden som ska plottas
N = 600;

%Lägger till array:er för att spara värdena som skickas från atmel
firststyrvarde =zeros(1,N);
secfelvarde =zeros(1,N);
thirdborvarde =zeros(1,N);
fourthcurrentvalue = zeros(1,N);
tid = zeros(1,N);
    
% For-loop där vi tar in alla värden och plottar dom.
for i=1:N
    
    flushinput(s);
    
    tid(i) =i;
    %Läser in värden
    tempfirststyrvarde = fscanf(s)
    tempsecfelvarde = fscanf(s)
    tempthirdborvarde = fscanf(s)
    tempfourthcurrentvalue = fscanf(s)
    
    %Gör om dom från string till double så att vi kan plotta dom
    firststyrvarde(i) =str2double(tempfirststyrvarde);
    secfelvarde(i) =str2double(tempsecfelvarde);
    thirdborvarde(i) =str2double(tempthirdborvarde);
    fourthcurrentvalue(i) = str2double(tempfourthcurrentvalue);
    
    %plottnigen
    plot(tid,firststyrvarde,'k--',tid,secfelvarde,'g--',tid,thirdborvarde,'b--',tid,fourthcurrentvalue,'r--');
    title('förhållandet från objekt till sensorn');
    xlabel('Sampling');
    ylabel('avstånd från sensor[cm]');
    legend('styrvärde','felvärde','Börvärde','pingisbollens avstånd');
    grid on
    drawnow;
    
end    
disp('done');
fclose(s);
delete(s);