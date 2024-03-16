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
end
