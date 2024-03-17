# frozen_string_literal: true

require 'bit_array'

RSpec.describe BitArray do
  describe '::new' do
    it 'returns a new bit array instance of the desired size' do
      expect { BitArray.new(10) }.not_to raise_error(ArgumentError)
    end

    it 'returns a new bit array instance based on some given binary string' do
      expect { BitArray.new([255, 10, 20].pack('C*')) }.not_to raise_error(
        ArgumentError
      )
    end

    it(
      'returns a new bit array instance using some given element size in bits'
    ) do
      expect { BitArray.new(100, bits_per_item: 64) }.not_to raise_error(
        ArgumentError
      )
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
end
