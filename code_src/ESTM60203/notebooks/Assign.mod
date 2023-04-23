
set RESOURCES;
set TASKS;

param a {RESOURCES,TASKS} >= 0;

var x {RESOURCES,TASKS} binary;

minimize Cost: sum{r in RESOURCES, t in TASKS} a[r,t]*x[r,t];
subject to R {r in RESOURCES}: sum {t in TASKS} x[r,t] = 1;
subject to T {t in TASKS}: sum {r in RESOURCES} x[r,t] = 1;

solve;

printf "\n\n";
for {r in RESOURCES} {
   for {t in TASKS : x[r,t] == 1} {
      printf "Assign %10s   to %10s   Cost: %6.0f\n", r, t, a[r,t];
   }
}
printf "\n\n";

end;
