function sdlk_setup(altitude,fc,df,baud,framesize)

% This fellas purpose is to setup the workspace variables for the downlink
% Assume a 4-FSK Modulation Scheme
%% Initialization
sdlk.altitude = altitude; % [km] {fspl}
sdlk.carrierfrequency = fc; % [MHz] {fspl}
sdlk.datarate = baud; % [bits/second] {bbg}
sdlk.bitsperframe = framesize; % [bits] {bbg}
sdlk.deltaf = df; %[MHz] {4fsk}
sdlk.M = Mary; % [] {4fsk}

%% Internal
sdlk.k = log2(Mary); % [bits/signal] {4fsk}

%% Comment structure:
% sdlk.parameter = argument; % [units] {relevant blocks} 
%% Dictionary of relevant blocks
% fspl = "Free Space Path Loss"
% bbg = "Bernoulli Binary Generator"
% 4fsk = "4-FSK Modulation Baseband"