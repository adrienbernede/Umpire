.. _device_allocators:

=================
Device Allocators
=================

The DeviceAllocator is designed for memory allocations on the GPU. 
Currently there is only support for CUDA, although HIP support is coming soon.

Creating a Device Allocator
--------------------------

To create a DeviceAllocator, users can call the :class:`umpire::make_device_allocator` host function.
This function takes an allocator, the total amount of memory the DeviceAllocator will have, and a name
for the new DeviceAllocator object, as shown below. Currently, a maximum of 64 DeviceAllocators can be
created at a time.

.. literalinclude:: ../../../examples/device-allocator.cpp
   :start-after: _sphinx_tag_make_dev_allocator_start
   :end-before: _sphinx_tag_make_dev_allocator_end
   :language: C++

When the DeviceAllocator is created, the ``size`` parameter that is passed to the :class:`umpire::make_device_allocator`
function is the total memory, in bytes, available to that allocator. Whenever the ``allocate`` function is
called on the GPU, it is simply atomically incrementing a counter which offsets a pointer to the start of that
memory.

Retrieving a DeviceAllocator Object
-----------------------------------

The :class:`umpire::get_device_allocator` host/device function returns the DeviceAllocator object that corresponds 
to the ID or name given. The DeviceAllocator class also includes a helper function, :class:`umpire::is_device_allocator`,
to query whether or not a given ID corresponds to an existing DeviceAllocator. Below is an example of using the **ID** to 
obtain the DeviceAllocator object:

.. literalinclude:: ../../../examples/device-allocator.cpp
   :start-after: _sphinx_tag_get_dev_allocator_id_start
   :end-before: _sphinx_tag_get_dev_allocator_id_end
   :language: C++

And next is an example of using the **name** instead:

.. literalinclude:: ../../../examples/device-allocator.cpp
   :start-after: _sphinx_tag_get_dev_allocator_name_start
   :end-before: _sphinx_tag_get_dev_allocator_name_end
   :language: C++

With the :class:`umpire::get_device_allocator` function, there is no need to keep track of the DeviceAllocator.
Users can instead use this function to obtain it inside whichever kernel they need.

Under the hood, the :class:`umpire::get_device_allocator` uses global arrays which can be accessed by both 
the host and device. The global array is indexed by DeviceAllocator ID, which is returned by :class:`DeviceAllocator::getID()`. 
Because we are using global arrays on host and device, the arrays need to be "set up" after the DeviceAllocators 
are created, but before any kernels are called. This process is done by calling the ``UMPIRE_SET_UP_DEVICE_ALLOCS()`` 
macro. This just ensures that the host and device global arrays are updated and pointing at the same memory.

.. note::
   In order to use the full capabilities of the DeviceAllocator, relocatable device code must be enabled.

Currently, the memory that has been used with the DeviceAllocator is only freed at the end of a program when the 
ResourceManager is torn down. However, there will be a :class:`DeviceAllocator::reset()` method implemented soon 
which will allow users to overwrite old data.

.. literalinclude:: ../../../examples/device-allocator.cpp
