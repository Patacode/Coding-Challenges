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
    if index.is_a?(Range)
      parsed_begin = index.begin || 0
      parsed_end = index.end || @size - 1
      lower_bound = parsed_begin
      upper_bound = index.exclude_end? ? parsed_end - 1 : parsed_end

      raise RangeError, "lower bound" if lower_bound < 0 || lower_bound >= @size
      raise RangeError, "upper bound" if upper_bound < 0 || upper_bound >= @size

      return [] if lower_bound > upper_bound

      res = []
      upper_size = @size < @bits_per_item ? @size : @bits_per_item
      lower_pow = upper_size - lower_bound
      upper_pow = upper_bound < upper_size ? upper_size - upper_bound - 1 : 0
      mask = 2**lower_pow - 2**upper_pow
      res << (@internal_array[0] & mask)

      item_index = 1
      items_count = (upper_bound / @bits_per_item) + 1

      processed_bound = items_count - 1
      while item_index < processed_bound
        res << @internal_array[item_index]
        item_index += 1
      end

      if items_count > 1
        remaining_bits = @size - (@bits_per_item * (items_count - 1))
        offset = remaining_bits - (upper_bound % remaining_bits) - 1
        res << (@internal_array[-1] >> offset)
      end

      res
    else
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
  end

  def []=(index, value)
    raise IndexError if index < 0 || index >= @size

    bit = value ? (value.is_a?(Integer) ? (value.zero? ? 0 : 1) : 1) : 0
    item_index = index / @bits_per_item
    item_bit_size = @internal_array[item_index].bit_length
    offset = item_bit_size - (index % @bits_per_item) - 1 

    if bit == 1
      @internal_array[item_index] |= 2**offset
    else
      @internal_array[item_index] &= (2**offset) - 1
    end
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
