# frozen_string_literal: true

class BitArray
  attr_reader :size, :bits_per_item

  def initialize(initial_data, bits_per_item: 64)
    raise ArgumentError if bits_per_item < 1 || bits_per_item > 64

    @size = init_size(initial_data)
    @internal_array = init_internal_array(initial_data, @size, bits_per_item)
    @bits_per_item = bits_per_item
  end

  def internal_array_clone
    @internal_array.clone
  end

  def [](index)
    raise IndexError if index < 0 || index >= size

    item_index = index / bits_per_item
    offset = @internal_array[item_index].bit_length - index - 1

    (@internal_array[item_index] >> offset) & 0x1
  end

  def []=(index, value)
    bit =
      if value.is_a?(Integer)
        value.zero? ? 0 : 1
      else
        value ? 1 : 0
      end

    return if bit.zero? 

    item_index = index / bits_per_item
    offset = bits_per_item - index

    @internal_array[item_index] |= (2**offset >> 1)
  end

  private

  def init_size(initial_data)
    initial_data.is_a?(String) ? initial_data.bytesize * 8 : initial_data
  end

  def init_internal_array(initial_data, size, bits_per_item)
    res = [0] * (size / bits_per_item.to_f).ceil
    return res unless initial_data.is_a?(String)

    item_pointer = -1
    bits_processed = 0
    initial_data.each_byte do |byte|
      item_pointer += 1 if (bits_processed % bits_per_item).zero?
      bits_processed += 8

      res[item_pointer] <<= 8
      res[item_pointer] |= byte
    end

    res
  end

  alias at []
  alias set []=
end
