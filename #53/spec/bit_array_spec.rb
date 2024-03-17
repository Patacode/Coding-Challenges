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
      expect { BitArray.new(100, bits_per_item: 0) }.to raise_error(ArgumentError)
      expect { BitArray.new(100, bits_per_item: 65) }.to raise_error(ArgumentError)
    end
  end
end
