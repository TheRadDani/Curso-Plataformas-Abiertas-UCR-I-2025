# mpi_hello.py
from mpi4py import MPI

def main():
    # Initialize MPI
    comm = MPI.COMM_WORLD # Global communicator
    rank = comm.Get_rank() # Current process ID
    size = comm.Get_size() # Total number of processes

    # Basic hello from each process
    print(f"Hello from process {rank} of {size}!")

    # Synchronize processes
    comm.Barrier()

    # Root process collects data
    if rank == 0:
        print("\n=== Gathering results ===")
        data = comm.gather(rank, root=0)
        print(f"Root received: {data}")
    else:
        comm.gather(rank, root=0)

if __name__ == "__main__":
    main()