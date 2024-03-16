# frozen_string_literal: true

require 'bloom_filter'

RSpec.describe BloomFilter do
  before(:context) do
    @bloom_filter = BloomFilter.new('dict_sample.txt', epsilon: 0.1)
  end

  describe '#size' do
    it 'returns the number of bits used by the bloom filter' do
      expect(@bloom_filter.size).to eq(480)
    end
  end

  describe '#hash_function_count' do
    it 'returns the number of hash functions used by the bloom filter' do
      expect(@bloom_filter.hash_function_count).to eq(4)
    end
  end

  describe '#to_i' do
    it 'returns the bit array value as integer used by the bloom filter' do
      expect(@bloom_filter.to_i).to eq(
        '12700271158760067064329340718225424671980043543329009783377009459400' \
        '87273989570313276819506087179542471113271943694014107953142208471521' \
        '828171362'.to_i
      )
    end
  end

  describe '#add' do
    it 'adds the provided element to the bloom filter' do
      @bloom_filter.add('hello')

      expect(@bloom_filter.to_i).to eq(
        '12700271158760067064329340718225424671980043543329009783377009459400' \
        '87273989570313276819506087179542471113271943694647933253256323172270' \
        '179774050'.to_i
      )
    end
  end
end
