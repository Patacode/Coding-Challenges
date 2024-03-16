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
        '1270027115876006706432934071822542467198004354332900978337700945940' \
        '08727398957031327681950608717954247111327194369401410795314220847152' \
        '1828171362'.to_i
      )
    end
  end
end
