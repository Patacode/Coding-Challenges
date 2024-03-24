# frozen_string_literal: true

class BitArray
  attr_reader :size, :bits_per_item

  def initialize(initial_data, bits_per_item: 64)
    raise ArgumentError if bits_per_item < 1 || bits_per_item > 64
    raise ArgumentError if bits_per_item % 8 != 0

    @size = init_size(initial_data, bits_per_item)
    @internal_array = init_internal_array(initial_data, @size, bits_per_item)
    @bits_per_item = bits_per_item
  end

  def [](index)
    raise IndexError if index < 0 || index >= @size

    item_index = index / @bits_per_item
    item_bit_size =
      if item_index == @internal_array.length - 1
        @size - ((@internal_array.length - 1) * @bits_per_item)
      else
        @bits_per_item
      end
    offset = item_bit_size - (index % @bits_per_item) - 1 

    (@internal_array[item_index] >> offset) & 0x1
  end

  def []=(index, value)
    raise IndexError if index < 0 || index >= @size

    bit = value ? (value.is_a?(Integer) ? (value.zero? ? 0 : 1) : 1) : 0
    item_index = index / @bits_per_item
    item_bit_size =
      if item_index == @internal_array.length - 1
        @size - ((@internal_array.length - 1) * @bits_per_item)
      else
        @bits_per_item
      end
    offset = item_bit_size - (index % @bits_per_item) - 1 

    if bit == 1
      @internal_array[item_index] |= 2**offset
    else
      @internal_array[item_index] &= ((2**item_bit_size) - 1) - 2**offset
    end
  end

  def each_byte(&proc)
    res = @internal_array.reduce([]) do |acc, item|
      offset = @bits_per_item
      while offset > 0
        offset -= 8
        acc << ((item >> offset) & 0b1111_1111)
      end

      acc
    end

    if proc
      res.each { |byte| proc.call(byte) }
    else
      res.each
    end
  end

  def to_a
    @internal_array.clone
  end

  def to_s
    @internal_array.map do |item|
      format("%0#{@bits_per_item}d", item.to_s(2))
    end.join(' ')
  end

  private

  def init_size(initial_data, bits_per_item)
    if initial_data.is_a?(Array)
      bits_per_item * initial_data.length
    else
      initial_data
    end
  end

  def init_internal_array(initial_data, size, bits_per_item)
    res = [0] * (size / bits_per_item.to_f).ceil
    initial_data.is_a?(Array) ? initial_data.clone : res
  end

  alias at []
  alias set []=
end
