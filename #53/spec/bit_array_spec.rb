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

  describe '#[]' do
    it 'returns the value of the bit at given index' do
      bit_array = BitArray.new([148, 145, 5].pack('C*'), bits_per_item: 8)

      expect(bit_array[0]).to eq(1)
      expect(bit_array[8]).to eq(1)
      expect(bit_array[14]).to eq(0)
      expect(bit_array[18]).to eq(1)
    end

    it 'raises an IndexError if given index is out of bounds' do
      bit_array = BitArray.new(10)

      expect { bit_array[-1] }.to raise_error(IndexError)
      expect { bit_array[10] }.to raise_error(IndexError)
    end

    it(
      'returns the bits found in the given range in the same format as the ' \
      'one used internally'
    ) do
      bit_array1 = BitArray.new([255, 10, 20].pack('C*'))
      bit_array2 = BitArray.new([255, 10, 20].pack('C*'), bits_per_item: 16)

      expect(bit_array1[5..]).to eq([461332])
      expect(bit_array2[1...23]).to eq([32522, 10])
    end

    it 'raises an RangeError if given range indexes are out of bounds' do
      bit_array = BitArray.new(10)

      expect { bit_array[-1..] }.to raise_error(RangeError)
      expect { bit_array[2..10] }.to raise_error(RangeError)
    end
  end

  describe '#[]=' do
    it 'sets the bit at given index to 1 if given value is truthy but 0' do
      bit_array = BitArray.new(10)

      bit_array[0] = []
      bit_array[2] = true
      bit_array[4] = 1
      bit_array[8] = 0 

      expect(bit_array[0]).to eq(1)
      expect(bit_array[2]).to eq(1)
      expect(bit_array[4]).to eq(1)
      expect(bit_array[8]).not_to eq(1)
    end

    it 'sets the bit at given index to 0 if given value is falsy or 0' do
      bit_array = BitArray.new(10)

      bit_array[0] = nil
      bit_array[2] = false
      bit_array[4] = 0

      expect(bit_array[0]).to eq(0)
      expect(bit_array[2]).to eq(0)
      expect(bit_array[4]).to eq(0)
    end
  end

  describe '#at' do
    it 'returns the value of the bit at given index (acts as #[])' do
      bit_array = BitArray.new([255, 10, 20].pack('C*'))

      expect(bit_array.at(0)).to eq(1)
      expect(bit_array.at(8)).to eq(0)
    end

    it 'raises an IndexError if given index is out of bounds (acts as #[])' do
      bit_array = BitArray.new(10)

      expect { bit_array.at(-1) }.to raise_error(IndexError)
      expect { bit_array.at(10) }.to raise_error(IndexError)
    end
  end

  describe '#set' do
    it(
      'sets the bit at given index to 1 if given value is truthy but 0 ' \
      '(acts as #[]=)'
    ) do
      bit_array = BitArray.new(10)

      bit_array.set(0, [])
      bit_array.set(2, true)
      bit_array.set(4, 1)
      bit_array.set(8, 0)

      expect(bit_array[0]).to eq(1)
      expect(bit_array[2]).to eq(1)
      expect(bit_array[4]).to eq(1)
      expect(bit_array[8]).not_to eq(1)
    end

    it(
      'sets the bit at given index to 0 if given value is falsy or 0 ' \
      '(acts as #[]=)'
    ) do
      bit_array = BitArray.new(10)

      bit_array.set(0, nil)
      bit_array.set(2, false)
      bit_array.set(4, 0)

      expect(bit_array[0]).to eq(0)
      expect(bit_array[2]).to eq(0)
      expect(bit_array[4]).to eq(0)
    end
  end
end
