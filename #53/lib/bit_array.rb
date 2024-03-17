class BitArray
  attr_reader :size

  def initialize(initial_data, bits_per_item: 64)
    raise ArgumentError if bits_per_item < 1 || bits_per_item > 64

    @size =
      initial_data.is_a?(String) ? initial_data.bytesize * 8 : initial_data
  end
end
