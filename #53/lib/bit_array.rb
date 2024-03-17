class BitArray
  def initialize(initial_data, bits_per_item: 64)
    raise ArgumentError if bits_per_item < 1 || bits_per_item > 64
  end
end
