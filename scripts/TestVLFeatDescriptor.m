%I = zeros(256,240);
%I(128,:)=255;
%I(10,120) = 255;
run('../vlfeat/toolbox/vl_setup')

FC = []

% Because the image in VlFeat Matlab is transposed, you need
% to transpose the keypoint location.
fc = [240/2;256/2;3;3;pi/2];
FC = [FC [fc]];

imagescale = 1;

output = zeros(256,1);

[eegimg, DOTS] = eegimage(1,output(:,1),1,1, false,240,false,false);

% VLFeat matlab implementation is transposed.  This means that you need 
% to provide the image transposed to have in the same direction that you 
% have if you access the VLFeat library directly.
[frames, descriptors] = vl_sift(single(eegimg'),'frames',fc,'floatdescriptors','octaves',1,'firstoctave',0,'verbose','verbose','verbose');

% The transpose issue means you have to transpose the first too coordinates
% of the frame (keypoint location)
DisplayDescriptorImageByImage([frames(2) ;frames(1); frames(3); frames(4);frames(5)],descriptors,eegimg,-1,true)

%DisplayDescriptorGradient('./grads.txt')