boolean test_and_set(boolean * target) {
  boolean rv = *target;
  *target = true;
  return rv;
}

int main() {
  do {
    while (test_and_set(&lock))
      ; // do nothing
    // critical section
    lock = false;
    // remainder
  } while(true);
}
