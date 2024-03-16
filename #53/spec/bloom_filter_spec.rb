require 'bloom_filter'

RSpec.describe BloomFilter do
  before(:context) do
    @bloom_filter = BloomFilter.new('dict_sample.txt')
  end

  describe '#include?' do
    it 'returns true if the provided value is probably in the set' do
      expect(@bloom_filter.include?('coding')).to be(true)
    end

    it 'returns false if the provided value is probably not in the set' do
      expect(@bloom_filter.include?('albito')).to be(false)
    end
  end
end
