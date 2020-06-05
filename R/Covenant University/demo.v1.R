calculate <- function(x, y) { (x + y) * (x + y); }
map <- function(vector, mapper) {
  for (element in vector) vector[element] <- mapper(element);
  vector
}
reduce <- function(vector) {
  accumulator <- 0;
  for (element in vector) accumulator <- accumulator + element;
  accumulator
}

calculate(2, 3);
map(c(1:3), function(element) { element * 3.5; });
matrix(1, ncol=10, nrow=10);
reduce(c(1:3))
