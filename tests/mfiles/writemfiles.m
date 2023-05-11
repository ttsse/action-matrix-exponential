type = "dense";
dense = true;
asdasd = "create"+type+"mats.m"; 
matf = fopen(asdasd,'w');

% size = [1000,2000,3000,4000,5000,6000,7000,8000,1000];
size = [10, 100, 1000, 2000];
% range = [5, 5, 5, 5, 5, 5, 5, 5, 5];
range = [5,5,5,5];
% shift  = [-2.5, -2.5, -2.5, -2.5, -2.5, -2.5, -2.5, -2.5, -2.5]*0;
shift = [-2.5,-2.5,-2.5,-2.5];
% t = [-1, -1, -1, -1, -1, -1, -1, -1, -1];
t = [-1,-1,-1,-1];
density = [0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.001];

fprintf(matf, "%s\n\n", "clear");
fprintf(matf, "mkdir %s\n\n", "../mat"+type+"files");

if (dense)
    for i = 1:length(size)
        fprintf(matf, "t = %f;\n", t(i));
        fprintf(matf,"A%d = %f*rand(%d,%d)+%f;\n",size(i),range(i),size(i),size(i),shift(i));
        fprintf(matf,"b%d = %f*rand(%d,1)+%f;\n",size(i),range(i),size(i),shift(i));
        fprintf(matf,"expmvtAb%d = expmv(t,A%d,b%d,[],'double');\n",size(i),size(i),size(i));
        fprintf(matf,"save(""%s"",""%s%d"",""%s%d"",%s,""%s%d"");\n","../mat"+type+"files/mat"+type+num2str(size(i))+".mat","A",size(i),"b",size(i),"""t""","expmvtAb",size(i));
        fprintf(matf,"clear\n\n");
    end
else
    for i = 1:length(size)
        fprintf(matf, "t = %f;\n", t(i));
        fprintf(matf,"A%d = %f*sprand(%d,%d,%f)+%f;\n",size(i),range(i),size(i),size(i),density(i),shift(i));
        fprintf(matf,"b%d = %f*rand(%d,1)+%f;\n",size(i),range(i),size(i),shift(i));
        fprintf(matf,"expmvtAb%d = expmv(t,A%d,b%d,[],'double');\n",size(i),size(i),size(i));
        fprintf(matf,"save(""%s"",""%s%d"",""%s%d"",%s,""%s%d"");\n","../mat"+type+"files/mat"+type+num2str(size(i))+".mat","A",size(i),"b",size(i),"""t""","expmvtAb",size(i));
        fprintf(matf,"clear\n\n");
    end
end

matf = fclose(matf);
