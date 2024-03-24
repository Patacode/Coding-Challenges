# frozen_string_literal: true

class BitArray
  attr_reader :size, :bits_per_item

  def initialize(initial_data, bits_per_item: 64)
    raise ArgumentError unless [8, 16, 32, 64].include?(bits_per_item)

    @size = init_size(initial_data, bits_per_item)
    @internal_array = init_internal_array(initial_data, @size, bits_per_item)
    @bits_per_item = bits_per_item
  end

  def [](index)
    raise IndexError if index.negative? || index >= @size

    item_index = index / @bits_per_item
    item_bit_size = compute_item_bit_size(item_index)
    offset = item_bit_size - (index % @bits_per_item) - 1

    (@internal_array[item_index] >> offset) & 0x1
  end

  def []=(index, value)
    raise IndexError if index.negative? || index >= @size

    bit = map_to_bit(value)
    item_index = index / @bits_per_item
    item_bit_size = compute_item_bit_size(item_index)
    offset = item_bit_size - (index % @bits_per_item) - 1

    if bit == 1
      set_bit(item_index, offset)
    else
      unset_bit(item_index, offset, item_bit_size)
    end
  end

  def each_byte(&proc)
    res = @internal_array.each_with_object([]) do |item, acc|
      offset = @bits_per_item
      while offset.positive?
        offset -= 8
        acc << ((item >> offset) & 0b1111_1111)
      end

      acc
    end

    proc ? res.each { |byte| proc.call(byte) } : res.each
  end

  def to_a
    @internal_array.clone
  end

  def to_s
    @internal_array.map do |item|
      format("%0#{@bits_per_item}d", item.to_s(2))
    end.join(' ')
  end

  def bits_per_item=(value)
    raise ArgumentError unless [8, 16, 32, 64].include?(value)

    if value > @bits_per_item
      increase_items_size(value)
    else
      decrease_items_size(value)
    end

    @bits_per_item = value
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

  def map_to_bit(value)
    if value
      if value.is_a?(Integer)
        value.zero? ? 0 : 1
      else
        1
      end
    else
      0
    end
  end

  def compute_item_bit_size(index)
    if index == @internal_array.length - 1
      size - ((@internal_array.length - 1) * @bits_per_item)
    else
      @bits_per_item
    end
  end

  def set_bit(index, offset)
    @internal_array[index] |= 2**offset
  end

  def unset_bit(index, offset, size)
    @internal_array[index] &= ((2**size) - 1) - (2**offset)
  end

  def increase_items_size(new_size)
    processed_bits = 0
    @internal_array = @internal_array.each_with_object([0]) do |item, acc|
      if processed_bits < new_size
        acc[-1] <<= @bits_per_item
        acc[-1] |= item
      else
        acc << item
        processed_bits = 0
      end
      processed_bits += @bits_per_item

      acc
    end

    fill_remaining_bits(processed_bits, new_size)
  end

  def fill_remaining_bits(processed_bits, new_size)
    while processed_bits < new_size
      @internal_array[-1] <<= @bits_per_item
      processed_bits += @bits_per_item
    end
  end

  def decrease_items_size(new_size)
    mask = (2**new_size) - 1
    @internal_array = @internal_array.each_with_object([]) do |item, acc|
      offset = @bits_per_item
      while offset.positive?
        offset -= new_size
        acc << ((item >> offset) & mask)
      end

      acc
    end
  end

  alias at []
  alias set []=
end
