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

  describe '#bits_per_item' do
    it 'returns the number of bits used by each item in the internal array' do
      bit_array = BitArray.new(10, bits_per_item: 54)

      expect(bit_array.bits_per_item).to eq(54)
    end

    it 'returns a default value of 64' do
      bit_array = BitArray.new(10)

      expect(bit_array.bits_per_item).to eq(64)
    end
  end

  describe '#internal_array_clone' do
    it 'returns accurately the internal array backed by the bit array' do
      bit_array1 = BitArray.new(10)
      bit_array2 = BitArray.new([255, 10, 20].pack('C*'))
      bit_array3 = BitArray.new([255, 10, 20].pack('C*'), bits_per_item: 16)
      bit_array4 = BitArray.new(16, bits_per_item: 8)

      expect(bit_array1.internal_array_clone).to eq([0])
      expect(bit_array2.internal_array_clone).to eq([16_714_260])
      expect(bit_array3.internal_array_clone).to eq([65_290, 20])
      expect(bit_array4.internal_array_clone).to eq([0, 0])
    end

    it 'returns a clone of the internal array backed by the bit array' do
      bit_array = BitArray.new(10)

      expect(bit_array.internal_array_clone).not_to be(
        bit_array.instance_variable_get(:@internal_array)
      )
    end
  end
end
