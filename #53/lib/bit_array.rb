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
    raise IndexError if index.negative? || index >= @size

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

    if value > @bits_per_item # increase
      processed_bits = 0
      @internal_array = @internal_array.reduce([0]) do |acc, item|
        if processed_bits < value
          acc[-1] <<= @bits_per_item
          acc[-1] |= item
        else
          acc << item
          processed_bits = 0
        end
        processed_bits += @bits_per_item

        acc
      end

      while processed_bits < value
        @internal_array[-1] <<= @bits_per_item
        processed_bits += @bits_per_item
      end
    else # decrease or nothing
      mask = 2**value - 1
      @internal_array = @internal_array.reduce([]) do |acc, item|
        offset = @bits_per_item
        while offset.positive?
          offset -= value
          acc << ((item >> offset) & mask)
        end

        acc
      end
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

  alias at []
  alias set []=
end
