# Multi-process-and-multi-thread-calculation-of-mean-absolute-deviation-and-range

Project Summary & Implementation Details:

The purpose of this project is to use and create multiple processes and threads within a process. Let's explain part by part:

For Part A, 
Range, which is the difference of the largest and smallest values in a set of data, was calculated in rangeFunction. The average of numbers was calculated using the meanFunction. MadFunction was written using the mean absolute deviation (MAD) algorithm and using the mean we calculated before. The results of all these are printed in the main part.

For Part B, 
The purpose of this section allows processes to communicate with each other and synchronize their actions by using inter-process communication (IPC) mechanism.
To achieve this, first of all, child and parent arrays were created to hold the necessary data (small and big numbers, mean and MAD values). The functions that calculate mean mad and range work the same as part A. We used a pointer in the range function to keep small and large values separately, and the initial index value in the mad function to do the work sharing correctly. We created an array in the child and parent functions and made them hold the values that they will process themselves. After separating these values, functions were called and small, big and average values were calculated for each. We used 2 pipes since there will be a data exchange again after calculating the mad functions. It is ensured that write-read operations between pipes are done in the proper order. 






Finally, the actual range and mean were calculated by comparing the values calculated separately for the child and the parent. After calculating the MAD with the mean value, the results were displayed on the screen.


For Part C, 
In multithreading part, our goal was to make another piece of code run in parallel while a piece of code is performing an operation. While doing this, we created a 2-dimensional array to reach certain values one by one as in Part B. Thus, we were able to reach the desired indexes (big, small numbers, mad and mean values) over a single variable. Unlike other parts, we used the numPart(count/thread) value in the mean function here, which determines how many values each thread will process.
In the thread function, we calculate the numPart we mentioned above with the number of threads entered by the user, we determine the starting indexes for each thread, and we find small and big values for these determined values.
In order to make sure that all threads have finished their work and then to be able to calculate MAD, we compare the number of flags we have created and increased and the number of threads and put them in a loop. 






We put the small and big values from each thread into the arrays to calculate the final range. We show the actual calculated range, mean and mad values on the screen.



Results

As a result, with this project, we have seen the differences in the duration and implementation of a process being shared to different processes and different threads.

Using PIPE, one of the IPC mechanisms, has been beneficial for 2 processes to communicate with each other and to reach a common MAD value. It was a logical solution to use pipes to enable them to communicate again after each process has done its own operations.

While we were doing the project, the implementation part of the pipes in Part B to provide the communication we mentioned above and the flag part in the loop that we used to wait for all the threads in Part C to finish their work were the most challenging parts for us.


