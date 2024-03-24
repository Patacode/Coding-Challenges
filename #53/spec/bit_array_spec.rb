# frozen_string_literal: true

require 'bit_array'

RSpec.describe BitArray do
  describe '::new' do
    it 'returns a new bit array of the desired size' do
      BitArray.new(10)
    end

    it 'returns a new bit array based on some given integer array' do
      BitArray.new([255, 10, 20])
    end

    it 'returns a new bit array using some given element size in bits' do
      BitArray.new(100, bits_per_item: 64)
    end

    it 'raises an ArgumentError if bits_per_item is < 8 or > 64' do
      expect { BitArray.new(100, bits_per_item: 7) }.to raise_error(
        ArgumentError
      )

      expect { BitArray.new(100, bits_per_item: 65) }.to raise_error(
        ArgumentError
      )
    end

    it 'raises an ArgumentError if bits_per_item is not a multiple of 8' do
      expect { BitArray.new(100, bits_per_item: 12) }.to raise_error(
        ArgumentError
      )
    end
  end

  describe '#size' do
    it 'returns the size of the bit array, in bits' do
      bit_array1 = BitArray.new(10)
      bit_array2 = BitArray.new([255, 10, 20])
      bit_array3 = BitArray.new(100, bits_per_item: 64)

      expect(bit_array1.size).to eq(10)
      expect(bit_array2.size).to eq(192)
      expect(bit_array3.size).to eq(100)
    end
  end

  describe '#bits_per_item' do
    it 'returns the number of bits used by each item in the internal array' do
      bit_array = BitArray.new(10, bits_per_item: 32)

      expect(bit_array.bits_per_item).to eq(32)
    end

    it 'returns a default value of 64' do
      bit_array = BitArray.new(10)

      expect(bit_array.bits_per_item).to eq(64)
    end
  end

  describe '#bits_per_item=' do
    it 'updates the bits used per item by merging existing ones (increase)' do
      bit_array = BitArray.new([255, 10, 20], bits_per_item: 16)

      bit_array.bits_per_item = 64

      expect(bit_array.to_a).to eq([71_776_162_012_200_960])
    end

    it 'updates the bits used per item by merging existing ones (decrease)' do
      bit_array = BitArray.new([255, 10, 20], bits_per_item: 16)

      bit_array.bits_per_item = 8

      expect(bit_array.to_a).to eq([0, 255, 0, 10, 0, 20])
    end

    it 'raises an ArgumentError if value is < 8 or > 64' do
      bit_array = BitArray.new(10)

      expect { bit_array.bits_per_item = 7 }.to raise_error(ArgumentError)
      expect { bit_array.bits_per_item = 65 }.to raise_error(ArgumentError)
    end

    it 'raises an ArgumentError if value is not multiple of 8' do
      bit_array = BitArray.new(10)

      expect { bit_array.bits_per_item = 9 }.to raise_error(ArgumentError)
    end
  end

  describe '#to_a' do
    it 'returns accurately the internal array backed by the bit array' do
      bit_array1 = BitArray.new(10)
      bit_array2 = BitArray.new([255, 10, 20])
      bit_array3 = BitArray.new([300, 10, 20], bits_per_item: 16)
      bit_array4 = BitArray.new(16, bits_per_item: 8)

      expect(bit_array1.to_a).to eq([0])
      expect(bit_array2.to_a).to eq([255, 10, 20])
      expect(bit_array3.to_a).to eq([300, 10, 20])
      expect(bit_array4.to_a).to eq([0, 0])
    end

    it 'returns a clone of the internal array backed by the bit array' do
      bit_array = BitArray.new(10)

      expect(bit_array.to_a).not_to be(
        bit_array.instance_variable_get(:@internal_array)
      )
    end
  end

  describe '#[]' do
    it 'returns the value of the bit at given index' do
      bit_array = BitArray.new([148, 145, 5], bits_per_item: 8)

      expect(bit_array[0]).to eq(1)
      expect(bit_array[8]).to eq(1)
      expect(bit_array[14]).to eq(0)
      expect(bit_array[23]).to eq(1)
    end

    it 'raises an IndexError if given index is out of bounds' do
      bit_array = BitArray.new(10)

      expect { bit_array[-1] }.to raise_error(IndexError)
      expect { bit_array[10] }.to raise_error(IndexError)
    end
  end

  describe '#[]=' do
    it 'sets the bit at given index to 1 if given value is truthy but 0' do
      bit_array = BitArray.new([148, 145, 5], bits_per_item: 8)

      bit_array[1] = []
      bit_array[14] = true
      bit_array[15] = 0
      bit_array[9] = 1

      expect(bit_array[1]).to eq(1)
      expect(bit_array[14]).to eq(1)
      expect(bit_array[15]).to eq(0)
      expect(bit_array[9]).to eq(1)
    end

    it 'sets the bit at given index to 0 if given value is falsy or 0' do
      bit_array = BitArray.new([148, 145, 5], bits_per_item: 8)

      bit_array[0] = nil
      bit_array[3] = false
      bit_array[16] = 0

      expect(bit_array[0]).to eq(0)
      expect(bit_array[3]).to eq(0)
      expect(bit_array[16]).to eq(0)
    end

    it 'raises an IndexError if given index is out of bounds' do
      bit_array = BitArray.new(10)

      expect { bit_array[-1] = 1 }.to raise_error(IndexError)
      expect { bit_array[10] = 0 }.to raise_error(IndexError)
    end
  end

  describe '#at' do
    it 'returns the value of the bit at given index (acts as #[])' do
      bit_array = BitArray.new([148, 145, 5], bits_per_item: 8)

      expect(bit_array.at(0)).to eq(1)
      expect(bit_array.at(8)).to eq(1)
      expect(bit_array.at(14)).to eq(0)
      expect(bit_array.at(23)).to eq(1)
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
      bit_array = BitArray.new([148, 145, 5], bits_per_item: 8)

      bit_array.set(1, [])
      bit_array.set(14, true)
      bit_array.set(15, 0)
      bit_array.set(9, 1)

      expect(bit_array[1]).to eq(1)
      expect(bit_array[14]).to eq(1)
      expect(bit_array[15]).to eq(0)
      expect(bit_array[9]).to eq(1)
    end

    it(
      'sets the bit at given index to 0 if given value is falsy or 0 ' \
      '(acts as #[]=)'
    ) do
      bit_array = BitArray.new([148, 145, 5], bits_per_item: 8)

      bit_array.set(0, nil)
      bit_array.set(3, false)
      bit_array.set(16, 0)

      expect(bit_array[0]).to eq(0)
      expect(bit_array[3]).to eq(0)
      expect(bit_array[16]).to eq(0)
    end

    it 'raises an IndexError if given index is out of bounds (acts as #[]=)' do
      bit_array = BitArray.new(10)

      expect { bit_array.set(-1, 1) }.to raise_error(IndexError)
      expect { bit_array.set(10, 0) }.to raise_error(IndexError)
    end
  end

  describe '#to_s' do
    it 'returns the binary string representation of the whole bit array' do
      bit_array1 = BitArray.new([148, 145, 5], bits_per_item: 8)

      expect(bit_array1.to_s).to eq('10010100 10010001 00000101')
    end
  end

  describe '#each_byte' do
    it 'iterates over each byte of the bit array' do
      bit_array = BitArray.new([255, 10, 20], bits_per_item: 8)

      index = 0
      bit_array.each_byte do |byte|
        case index
        when 0 then expect(byte).to eq(255)
        when 1 then expect(byte).to eq(10)
        when 2 then expect(byte).to eq(20)
        end

        index += 1
      end
    end

    it 'returns an enumerator if no callback is given' do
      bit_array = BitArray.new([255, 10, 20], bits_per_item: 8)

      expect(bit_array.each_byte).to be_an(Enumerator)
    end
  end
end
