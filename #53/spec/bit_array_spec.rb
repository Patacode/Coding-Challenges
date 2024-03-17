# frozen_string_literal: true

require 'bit_array'

RSpec.describe BitArray do
  describe '::new' do
    it 'returns a new bit array of the desired size' do
      BitArray.new(10)
    end

    it 'returns a new bit array based on some given binary string' do
      BitArray.new([255, 10, 20].pack('C*'))
    end

    it 'returns a new bit array using some given element size in bits' do
      BitArray.new(100, bits_per_item: 64)
    end

    it 'raises an ArgumentError if bits_per_item is < 1 or > 64' do
      expect { BitArray.new(100, bits_per_item: 0) }.to raise_error(
        ArgumentError
      )

      expect { BitArray.new(100, bits_per_item: 65) }.to raise_error(
        ArgumentError
      )
    end
  end

  describe '#size' do
    it 'returns the size of the bit array, in bits' do
      bit_array1 = BitArray.new(10)
      bit_array2 = BitArray.new([255, 10, 20].pack('C*'))
      bit_array3 = BitArray.new(100, bits_per_item: 64)

      expect(bit_array1.size).to eq(10)
      expect(bit_array2.size).to eq(24)
      expect(bit_array3.size).to eq(100)
    end
  end

  describe '#internal_array_clone' do
    it 'returns a clone of the internal array backed by the bit array' do
      bit_array1 = BitArray.new(10)
      bit_array2 = BitArray.new([255, 10, 20].pack('C*'))
      bit_array3 = BitArray.new([255, 10, 20].pack('C*'), bits_per_item: 16)
      bit_array1 = BitArray.new(10, bits_per_item: 52)

      expect(bit_array1.internal_array_clone).to eq([0])
      expect(bit_array2.internal_array_clone).to eq([16714260])
      expect(bit_array3.internal_array_clone).to eq([65290, 20])
    end
  end
end
