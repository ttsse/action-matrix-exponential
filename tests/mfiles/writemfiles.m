type = "sparse";
dense = false;
asdasd = "create"+type+"mats.m"; 
matf = fopen(asdasd,'w');

size = [1000,2000,3000,4000,5000];

range = [5, 5, 5, 5, 5];

t = [-1, -1, -1, -1, -1];

density = [0.01, 0.01, 0.01, 0.01, 0.01];

fprintf(matf, "%s\n\n", "clear");
fprintf(matf, "mkdir %s\n\n", "../mat"+type+"files");

for i = 1:length(size)
    fprintf(matf, "t = %f;\n", t(i));
    fprintf(matf,"A%d = %f*sprandn(%d,%d,%f);\n",size(i),range(i),size(i),size(i),density(i));
    fprintf(matf,"b%d = %f*rand(%d,1);\n",size(i),range(i),size(i));
    fprintf(matf,"expmvtAb%d = expmv(t,A%d,b%d,[],'double');\n",size(i),size(i),size(i));
    fprintf(matf,"save %s %s%d %s%d %s %s%d -v7.3 -nocompression;\n","../mat"+type+"files/mat"+type+num2str(size(i))+".mat","A",size(i),"b",size(i),"t","expmvtAb",size(i));
    fprintf(matf,"clear\n\n");
end

matf = fclose(matf);
