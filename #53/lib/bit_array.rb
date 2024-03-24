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
    if index.is_a?(Range)
      bounded_start = index.begin || 0
      bounded_end = index.end || @size - 1
      bounded_end = index.exclude_end? ? bounded_end - 1 : bounded_end

      raise RangeError if bounded_start < 0 || bounded_start >= @size
      raise RangeError if bounded_end < 0 || bounded_end >= @size

      res = []
      item_index = bounded_start / @bits_per_item
      processed_bits = bounded_start
      left_over_bits = bounded_start % @bits_per_item
      last_item_bit_size =
        @size - ((@internal_array.length - 1) * @bits_per_item)

      while processed_bits <= bounded_end
        item_bit_size =
          if item_index == @internal_array.length - 1
            last_item_bit_size
          else
            @bits_per_item
          end
        offset = item_bit_size - (bounded_start % @bits_per_item)
        if item_index == @internal_array.length - 1
          end_offset = item_bit_size - (bounded_end % @bits_per_item) - 1
          res << (@internal_array[item_index] >> end_offset)
        else
          res << (@internal_array[item_index] & ((2**offset) - 1))
        end
        item_index += 1
        processed_bits += offset + left_over_bits

        if left_over_bits > 0 && item_index < @internal_array.length
          item_bit_size =
            if item_index == @internal_array.length - 1
              last_item_bit_size
            else
              @bits_per_item
            end
          bits_to_add =
            @internal_array[item_index] >> (item_bit_size - left_over_bits)
          res[item_index - 1] <<= left_over_bits
          res[item_index - 1] |= bits_to_add
        end
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
