# Memory access and performance

## Goal

Show that the same arithmetic sum can have different performance depending on
memory access pattern and working set size.

What is measured:

- sequential access: `sum += a[i]`
- stride access: `sum += a[(i*stride) % n]`
- random index access: `sum += a[idx[i]]` where `idx` is a shuffled permutation

How to run:

## Results

To be completed

## Background information

**Physical memory** consists of fixed-size page frames addressed via physical
addresses on the memory bus. Its constraints include hardware capacity,
fragmentation, and the lack of built-in process isolation.

**Virtual memory** abstracts this model. Each process sees a private,
contiguous virtual address space independent of the underlying DRAM layout.
Virtual pages map to physical page frames of identical size. The Memory
Management Unit (MMU) translates virtual addresses to physical addresses using
page tables. To avoid a page table walk on every access, the MMU maintains a
Translation Lookaside Buffer (TLB), a small associative cache of recent
virtual-to-physical translations. The OS manages virtual memory in units of
fixed-size pages.

**Virtual contiguity** (e.g., `std::vector`) does not imply physical
contiguity; adjacent virtual pages may map to unrelated physical frames. In
practice, performance is determined by cache locality, TLB coverage, and DRAM
row-buffer locality rather than by physical adjacency of pages.

**Main memory** (DRAM) accesses are comparatively slow, with latencies one to
two orders of magnitude higher than on-chip caches.

**Caches** sit between the CPU cores and DRAM to reduce effective memory
latency and hide the cost of these slow DRAM accesses. They are organized
hierarchically as L1 (closest to the CPU core, smallest, lowest latency), L2,
and L3 (farthest from the core, largest, highest latency, typically shared
across cores).

**Data transfer** between memory and CPU occurs in cache-line units (typically
64 bytes), independent of page size.

### Sequence of a memory access

1. The CPU issues a load/store using a virtual address.
2. Address translation: the MMU checks the TLB.
   - TLB hit: the physical address is obtained immediately.
   - TLB miss: hardware performs a page table walk. If the mapping is invalid,
     a page fault is raised and handled by the OS.
3. Data access: with the physical address resolved, CPU probes the cache
   hierarchy (typically L1 -> L2 -> L3).
   - Cache hit: data is returned.
   - Cache miss: the request proceeds to DRAM, and the corresponding cache line
     is fetched back up the hierarchy.

**Typical laptop-scale numbers** (per core unless noted). Latencies are
approximate and refer to cache-line access under low contention.

  | Memory        | Size                   | Latency    |
  | ---           | ---                    | ---        |
  | L1 data cache | 32 KiB (~4K doubles)   | ~1 ns      |
  | L2 cache      | 512 KiB (~65K doubles) | ~3-5 ns    |
  | L3 cache      | ~8 MiB shared          | ~10-15 ns  |
  | DRAM          | several GB             | ~80-120 ns |

**The dominant latency gap is between the last-level cache and DRAM.**
Cache-aware data layout and access patterns aim to keep the working set within
the cache hierarchy and minimize TLB and DRAM misses.
